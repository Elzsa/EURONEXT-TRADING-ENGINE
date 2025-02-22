#include "MatchingEngine.hpp"
#include <iostream>
#include <iomanip>

MatchingEngine::MatchingEngine(OrderBook& ob, InstrumentManager& im)
    : orderBook(ob), instrumentManager(im), isRunning(false) {
}

MatchingEngine::~MatchingEngine() {
    stop();
}

void MatchingEngine::start() {
    if (!isRunning) {
        isRunning = true;
        engineThread = std::thread(&MatchingEngine::run, this);
        std::cout << "Trading Engine started in continuous mode." << std::endl;
    }
}

void MatchingEngine::stop() {
    if (isRunning) {
        isRunning = false;
        if (engineThread.joinable()) {
            engineThread.join();
        }
        std::cout << "Trading Engine stopped." << std::endl;
    }
}

bool MatchingEngine::isEngineRunning() const {
    return isRunning;
}

void MatchingEngine::run() {
    auto lastStatusUpdate = std::chrono::system_clock::now();
    auto lastGTDCheck = std::chrono::system_clock::now();

    while (isRunning) {
        try {
            auto now = std::chrono::system_clock::now();

            // Convertir le chrono::time_point en time_t pour l'affichage
            auto now_time_t = std::chrono::system_clock::to_time_t(now);

            // Tenter les appariements
            int matches = orderBook.matchOrders();
            if (matches > 0) {
                std::cout << "\nMatched " << matches << " orders at "
                         << std::put_time(std::localtime(&now_time_t), "%H:%M:%S") << std::endl;
            }

            // Vérification des ordres GTD
            if (now - lastGTDCheck > std::chrono::hours(1)) {
                std::cout << "\nChecking GTD orders at "
                         << std::put_time(std::localtime(&now_time_t), "%H:%M:%S") << std::endl;
                checkGTDOrders();
                lastGTDCheck = now;
            }

            // Affichage du statut
            if (now - lastStatusUpdate > std::chrono::minutes(1)) {
                std::cout << "\n=== Status Update at "
                         << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M:%S")
                         << " ===" << std::endl;
                displayEngineStatus();
                lastStatusUpdate = now;
            }

            // Pause pour éviter la surcharge CPU
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        catch (const std::exception& e) {
            std::cerr << "\nError in trading engine: " << e.what() << std::endl;
        }
    }
}

void MatchingEngine::displayEngineStatus() const {
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    std::cout << "\n=== Trading Engine Status ===\n";
    std::cout << "Time: " << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M:%S") << "\n";
    std::cout << "Engine Status: " << (isRunning ? "Running" : "Stopped") << "\n";
    std::cout << "Number of instruments: " << instrumentManager.getInstruments().size() << "\n";
    std::cout << "Number of BID price levels: " << orderBook.bidOrders.size() << "\n";
    std::cout << "Number of ASK price levels: " << orderBook.askOrders.size() << "\n";
    std::cout << "==========================\n\n";
}

void MatchingEngine::checkGTDOrders() {
    auto now = std::chrono::system_clock::now();

    // Parcourir les ordres BID
    for (auto& [price, orders] : orderBook.bidOrders) {
        orders.erase(
            std::remove_if(orders.begin(), orders.end(),
                [now](const Order& order) {
                    if (order.timeinforce == TimeInForce::GTD && order.expirationDate <= now) {
                        std::cout << "Removing expired GTD order ID: " << order.idorder << std::endl;
                        return true;
                    }
                    return false;
                }),
            orders.end()
        );
    }

    // Parcourir les ordres ASK
    for (auto& [price, orders] : orderBook.askOrders) {
        orders.erase(
            std::remove_if(orders.begin(), orders.end(),
                [now](const Order& order) {
                    if (order.timeinforce == TimeInForce::GTD && order.expirationDate <= now) {
                        std::cout << "Removing expired GTD order ID: " << order.idorder << std::endl;
                        return true;
                    }
                    return false;
                }),
            orders.end()
        );
    }
}

bool MatchingEngine::addAndValidateOrder(const Order& order) {
    // Trouver l'instrument correspondant
    for (const auto& instrument : instrumentManager.getInstruments()) {
        if (instrument.idinstrument == order.idinstrument &&
            instrument.marketIdentificationCode == order.marketIdentificationCode &&
            instrument.tradingCurrency == order.tradingCurrency) {

            if (order.validatePrice(instrument) && order.validateQuantity(instrument)) {
                orderBook.addOrder(order);
                return true;
            }
            break;
        }
    }
    return false;
}