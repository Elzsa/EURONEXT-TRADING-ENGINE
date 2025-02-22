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

int main()
{
    std::cout << "=== EURONEXT TRADING ENGINE DEMONSTRATION ===\n\n";

    // Part 1: Initialize InstrumentManager and OrderBook
    std::cout << "Part 1: Initializing System Components\n";
    OrderBook orderBook;
    InstrumentManager instrumentManager;

    // Part 2: Add Instruments with uniqueness check
    std::cout << "\nPart 2: Adding Financial Instruments\n";
    instrumentManager.addInstrument(Instrument(1, "XPAR", "EUR", "AAPL", 20220101, State::ACTIVE,
                                               150, 1001, 100, 2, 1, 1, 2022));
    instrumentManager.addInstrument(Instrument(2, "XPAR", "EUR", "MSFT", 20220102, State::ACTIVE,
                                               2740.01, 1002, 400, 2, 2, 2, 2023));
    instrumentManager.addInstrument(Instrument(1, "XPAR", "EUR", "AAPL", 20220101, State::ACTIVE,
                                               150, 1001, 100, 2, 1, 1, 2022)); // Duplicate - should be rejected
    instrumentManager.addInstrument(Instrument(3, "XPAR", "GBP", "NVDI", 20220101, State::ACTIVE,
                                               150, 1001, 100, 2, 1, 1, 2022));

    const auto& instruments = instrumentManager.getInstruments();

    // Part 3: Create random orders for the instruments
    std::cout << "\nPart 3: Creating Initial Random Orders\n";
    auto now = std::chrono::system_clock::now();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> day_dist(1, 30);

    for (const auto& instrument : instruments)
    {
        TimeInForce timeInForce = getRandomEnumValue<TimeInForce>();
        OrderType orderType = getRandomEnumValue<OrderType>();
        LimitType limitType = getRandomEnumValue<LimitType>();

        std::chrono::system_clock::time_point expiration = now;
        if (timeInForce == TimeInForce::GTD)
        {
            expiration = now + std::chrono::hours(24 * day_dist(gen));
        }

        Order order;
        if (timeInForce == TimeInForce::DAY)
        {
            order = Order(instrument.idinstrument, instrument.marketIdentificationCode, instrument.tradingCurrency,
                          now, instrument.refprice, instrument.lotsize, timeInForce, orderType,
                          limitType, instrument.idinstrument, instrument.lotsize, 1001);
        }
        else
        {
            order = Order(instrument.idinstrument, instrument.marketIdentificationCode, instrument.tradingCurrency,
                          now, instrument.refprice, instrument.lotsize, timeInForce, orderType,
                          limitType, instrument.idinstrument, instrument.lotsize, 1001, expiration);
        }

        if (order.validatePrice(instrument) && order.validateQuantity(instrument))
        {
            std::cout << "Order validated for instrument " << order.idinstrument << " and added to the orderbook.\n";
            orderBook.addOrder(order);
        }
        else
        {
            std::cout << "Order rejected for instrument " << order.idinstrument << ".\n";
        }
    }

    std::cout << "\nInitial OrderBook State:\n";
    orderBook.displayOrderBook();

    // Part 4: Test the Price-Time Priority (PTP) Algorithm
    std::cout << "\nPart 4: Testing Price-Time Priority (PTP) Algorithm\n";

    // We'll use the first instrument for demonstration
    Instrument testInstrument = instruments[0];
    auto testTime = std::chrono::system_clock::now();

    std::cout << "Creating test orders for " << testInstrument.name << " (ID: " << testInstrument.idinstrument <<
        "):\n";

    // Create BID orders with high price
    Order bidOrder1(1001, testInstrument.marketIdentificationCode, testInstrument.tradingCurrency,
                    testTime, testInstrument.refprice + 5.0, testInstrument.lotsize * 3,
                    TimeInForce::DAY, OrderType::BID, LimitType::LIMIT,
                    testInstrument.idinstrument, testInstrument.lotsize * 3, 2001);

    // Same price but later timestamp - to test time priority
    Order bidOrder2(1002, testInstrument.marketIdentificationCode, testInstrument.tradingCurrency,
                    testTime + std::chrono::milliseconds(100), testInstrument.refprice + 5.0,
                    testInstrument.lotsize * 2, TimeInForce::DAY, OrderType::BID,
                    LimitType::LIMIT, testInstrument.idinstrument, testInstrument.lotsize * 2, 2002);

    // Create ASK orders with low price to facilitate matching
    Order askOrder1(2001, testInstrument.marketIdentificationCode, testInstrument.tradingCurrency,
                    testTime + std::chrono::milliseconds(200), testInstrument.refprice - 2.0,
                    testInstrument.lotsize * 4, TimeInForce::DAY, OrderType::ASK,
                    LimitType::LIMIT, testInstrument.idinstrument, testInstrument.lotsize * 4, 3001);

    // Higher price - may not match depending on available BID orders
    Order askOrder2(2002, testInstrument.marketIdentificationCode, testInstrument.tradingCurrency,
                    testTime + std::chrono::milliseconds(300), testInstrument.refprice + 3.0,
                    testInstrument.lotsize * 1, TimeInForce::DAY, OrderType::ASK,
                    LimitType::LIMIT, testInstrument.idinstrument, testInstrument.lotsize * 1, 3002);

    // Add and validate orders
    if (bidOrder1.validatePrice(testInstrument) && bidOrder1.validateQuantity(testInstrument))
    {
        std::cout << "BID order 1: Price " << bidOrder1.price << ", Quantity " << bidOrder1.quantity << " - Added\n";
        orderBook.addOrder(bidOrder1);
    }

    if (bidOrder2.validatePrice(testInstrument) && bidOrder2.validateQuantity(testInstrument))
    {
        std::cout << "BID order 2: Price " << bidOrder2.price << ", Quantity " << bidOrder2.quantity << " - Added\n";
        orderBook.addOrder(bidOrder2);
    }

    if (askOrder1.validatePrice(testInstrument) && askOrder1.validateQuantity(testInstrument))
    {
        std::cout << "ASK order 1: Price " << askOrder1.price << ", Quantity " << askOrder1.quantity << " - Added\n";
        orderBook.addOrder(askOrder1);
    }

    if (askOrder2.validatePrice(testInstrument) && askOrder2.validateQuantity(testInstrument))
    {
        std::cout << "ASK order 2: Price " << askOrder2.price << ", Quantity " << askOrder2.quantity << " - Added\n";
        orderBook.addOrder(askOrder2);
    }

    // Explicitly call matchOrders to ensure matching has been attempted
    std::cout << "\nAttempting to match orders...\n";
    int numMatches = orderBook.matchOrders();
    std::cout << "Number of matches executed: " << numMatches << "\n";

    // Display final state
    std::cout << "\nFinal OrderBook State:\n";
    orderBook.displayOrderBook();

    std::cout << "\nTrade History:\n";
    orderBook.displayTrades();

    // Création et démarrage du MatchingEngine
    MatchingEngine engine(orderBook, instrumentManager);
    engine.start();

    // Interface utilisateur interactive
    std::string command;
    while (true)
    {
        std::cout << "\nEnter command (status/order/display/quit): ";
        std::getline(std::cin, command);

        if (command == "status")
        {
            engine.displayEngineStatus();
        }
        else if (command == "order")
        {
            // Pour simuler l'ajout d'un nouvel ordre
            Order testOrder = bidOrder1; // Utiliser un ordre de test existant
            testOrder.idorder++; // Incrémenter l'ID pour le rendre unique
            if (engine.addAndValidateOrder(testOrder))
            {
                std::cout << "New order added successfully\n";
            }
            else
            {
                std::cout << "Failed to add new order\n";
            }
        }
        else if (command == "display")
        {
            orderBook.displayOrderBook();
            orderBook.displayTrades();
        }
        else if (command == "quit")
        {
            std::cout << "Stopping Trading Engine...\n";
            engine.stop();
            break;
        }
        else
        {
            std::cout << "Unknown command. Available commands: status/order/display/quit\n";
        }
    }

    std::cout << "\n=== END OF DEMONSTRATION ===\n";
    return 0;
}
