#include <iostream>
#include <set>
#include <chrono>
#include <random>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"
#include "../include/OrderBook.hpp"
#include "../include/Utils.hpp"
#include "../include/InstrumentManager.hpp"
#include "../include/MatchingEngine.hpp"

// Helper functions for generating random enum values (for testing only)
template <typename T>
int enumCount();

template <>
int enumCount<TimeInForce>() { return 2; }

template <>
int enumCount<OrderType>() { return 2; }

template <>
int enumCount<LimitType>() { return 2; }

template <typename T>
T getRandomEnumValue()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, enumCount<T>() - 1);
    return static_cast<T>(dis(gen));
}

int main() {
    std::cout << "=== EURONEXT TRADING ENGINE DEMONSTRATION ===\n\n";

    // Feature 1: System Initialization
    std::cout << "=== Feature 1: System Initialization ===\n";
    OrderBook orderBook;
    InstrumentManager instrumentManager;

    // Ajout d'instruments avec test d'unicité
    std::cout << "Testing Instrument Management:\n";
    instrumentManager.addInstrument(Instrument(1, "XPAR", "EUR", "AAPL", 20220101, State::ACTIVE,
                                             150, 1001, 100, 2, 1, 1, 2022));
    instrumentManager.addInstrument(Instrument(2, "XPAR", "EUR", "MSFT", 20220102, State::ACTIVE,
                                             2740.01, 1002, 400, 2, 2, 2, 2023));
    // Test de rejet des doublons
    std::cout << "\nTesting duplicate rejection:\n";
    instrumentManager.addInstrument(Instrument(1, "XPAR", "EUR", "AAPL", 20220101, State::ACTIVE,
                                             150, 1001, 100, 2, 1, 1, 2022));

    // Test d'instruments avec différentes devises
    instrumentManager.addInstrument(Instrument(3, "XPAR", "GBP", "NVDI", 20220101, State::ACTIVE,
                                             150, 1001, 100, 2, 1, 1, 2022));

    const auto& instruments = instrumentManager.getInstruments();
    std::cout << "\nTotal instruments registered: " << instruments.size() << "\n\n";

    // Feature 2: Price-Time Priority (PTP) Algorithm
    std::cout << "\n=== Feature 2: Price-Time Priority (PTP) Algorithm ===\n";
    auto now = std::chrono::system_clock::now();
    Instrument testInstrument = instruments[0]; // Using AAPL for testing

    std::cout << "\nCreating test orders with various prices and timestamps:\n";

    // Test 1: Basic PTP matching
    std::cout << "\nTest 1 - Basic PTP matching:\n";
    Order bidHighPrice(1001, "XPAR", "EUR", now, 155.0, 300,
                      TimeInForce::DAY, OrderType::BID, LimitType::LIMIT, 1, 300, 2001);
    Order askLowPrice(2001, "XPAR", "EUR", now + std::chrono::milliseconds(100),
                     148.0, 200, TimeInForce::DAY, OrderType::ASK, LimitType::LIMIT, 1, 200, 3001);

    orderBook.addOrder(bidHighPrice);
    orderBook.addOrder(askLowPrice);

    // Test 2: Time Priority at same price
    std::cout << "\nTest 2 - Time Priority at same price:\n";
    Order bidSamePrice1(1002, "XPAR", "EUR", now + std::chrono::milliseconds(200),
                       155.0, 200, TimeInForce::DAY, OrderType::BID, LimitType::LIMIT, 1, 200, 2002);
    Order bidSamePrice2(1003, "XPAR", "EUR", now + std::chrono::milliseconds(300),
                       155.0, 200, TimeInForce::DAY, OrderType::BID, LimitType::LIMIT, 1, 200, 2003);

    orderBook.addOrder(bidSamePrice1);
    orderBook.addOrder(bidSamePrice2);

    // Test 3: GTD Orders
    std::cout << "\nTest 3 - GTD Orders:\n";
    Order gtdOrder(3001, "XPAR", "EUR", now, 152.0, 100,
                  TimeInForce::GTD, OrderType::ASK, LimitType::LIMIT, 1, 100, 4001,
                  now + std::chrono::hours(24));

    orderBook.addOrder(gtdOrder);

    std::cout << "\nOrderBook after initial orders:\n";
    orderBook.displayOrderBook();

    // Feature 5: Continuous Trading Mode
    std::cout << "\n=== Feature 5: Continuous Trading Mode ===\n";
    MatchingEngine engine(orderBook, instrumentManager);

    std::cout << "\nStarting Trading Engine in continuous mode...\n";
    engine.start();

    // Interface interactive
    std::cout << "\nAvailable commands:\n";
    std::cout << "  status  - Display current engine status\n";
    std::cout << "  order   - Add a new test order\n";
    std::cout << "  display - Show order book and trades\n";
    std::cout << "  quit    - Stop the engine and exit\n";

    std::string command;
    while (true) {
        std::cout << "\nCommand > ";
        std::getline(std::cin, command);

        if (command == "status") {
            engine.displayEngineStatus();
        }
        else if (command == "order") {
            // Création d'un ordre de test alternant entre BID et ASK
            static bool isBid = true;
            static int orderId = 5000;

            Order newOrder(orderId++, "XPAR", "EUR",
                         std::chrono::system_clock::now(),
                         isBid ? 155.0 : 148.0, // Prix alterné
                         100,
                         TimeInForce::DAY,
                         isBid ? OrderType::BID : OrderType::ASK,
                         LimitType::LIMIT,
                         1, 100, 1001);

            if (engine.addAndValidateOrder(newOrder)) {
                std::cout << "Added new " << (isBid ? "BID" : "ASK") << " order\n";
                isBid = !isBid; // Alterner pour le prochain ordre
            }
        }
        else if (command == "display") {
            orderBook.displayOrderBook();
            orderBook.displayTrades();
        }
        else if (command == "quit") {
            std::cout << "Stopping Trading Engine...\n";
            engine.stop();
            break;
        }
        else {
            std::cout << "Unknown command. Available commands: status/order/display/quit\n";
        }
    }

    std::cout << "\n=== END OF DEMONSTRATION ===\n";
    return 0;
}
