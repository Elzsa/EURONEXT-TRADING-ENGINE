//
// Created by PAYA Elsa on 08/01/2025.
//

#include <iostream>
#include <set>
#include <chrono>
#include <random>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"
#include "../include/OrderBook.hpp"
#include "../include/Utils.hpp"
#include "../include/InstrumentManager.hpp"

// ToDo_END : Only for testing, delete when connecting code

// Fonction used to generate random states for different enum classes written in Instrument.hpp
template <typename T>
int enumCount();
// Specialisations for each type of enumeration
template <>
int enumCount<TimeInForce>() {
    return 2;  // TimeInForce is either GTD or DAY
}
template <>
int enumCount<OrderType>() {
    return 2;  // OrderType is either BID or ASK
}
template <>
int enumCount<LimitType>() {
    return 2;  // LimitType is either LIMIT or NONE
}

// Actual function to generate random states for testing
template <typename T>
T getRandomEnumValue() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, enumCount<T>() - 1); // Utiliser enumCount pour déterminer la plage

    return static_cast<T>(dis(gen));
}
// END OF PART FOR TESTING




int main() {

    // OrderBook creation
    OrderBook orderBook;
    // set to check unicity of instrument'id triplet (idinstrument, marketIdentificationCode and tradingCurrency)
    std::set<std::tuple<int, std::string, std::string>> instrumentSet;
    // Observer Pattern for instrument
    InstrumentManager instrumentManager;

    // Creation of instruments and check of unicity in ids
    instrumentManager.addInstrument(Instrument(1, "XPAR", "EUR", "AAPL", 20220101, State::ACTIVE,
                                               150, 1001, 100, 2, 1, 1, 2022));
    instrumentManager.addInstrument(Instrument(2, "XPAR", "EUR", "MSFT", 20220102, State::ACTIVE,
                                               2740.01, 1002, 400, 2, 2, 2, 2023));
    instrumentManager.addInstrument(Instrument(1, "XPAR", "EUR", "AAPL", 20220101, State::ACTIVE,
                                               150, 1001, 100, 2, 1, 1, 2022)); // Doublon donc instrument refusé
    instrumentManager.addInstrument(Instrument(3, "XPAR", "GBP", "NVDI", 20220101, State::ACTIVE,
                                           150, 1001, 100, 2, 1, 1, 2022));


    // Take instruments that where accepted as valid (unicity of keys checker)
    const auto& instruments = instrumentManager.getInstruments();

    // Creation of orders for each validated instruments
    auto now = std::chrono::system_clock::now();
    for (const auto& instrument : instruments) {
        // Sélection aléatoire des attributs
        TimeInForce timeInForce = getRandomEnumValue<TimeInForce>();
        OrderType orderType = getRandomEnumValue<OrderType>();
        LimitType limitType = getRandomEnumValue<LimitType>();

        // ToDo_END Only for testing, delete when connecting code
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> day_dist(1, 30); // Generate an int between 1 and 30 (these are days)
        // END OF PART FOR TESTING

        // If the order is a GTD order, we create the expiration
        std::chrono::system_clock::time_point expiration = now;
        if (timeInForce == TimeInForce::GTD) {
            expiration = now + std::chrono::hours(24 * day_dist(gen)); // random expiry (between 1 and 30 days)
        }

        // actual order creation
        Order order;
        if (timeInForce == TimeInForce::DAY) {
            order = Order(instrument.idinstrument, instrument.marketIdentificationCode, instrument.tradingCurrency,
                          now, instrument.refprice, instrument.lotsize, timeInForce, orderType,
                          limitType, instrument.idinstrument, instrument.lotsize, 1001);
        } else {
            order = Order(instrument.idinstrument, instrument.marketIdentificationCode, instrument.tradingCurrency,
                          now, instrument.refprice, instrument.lotsize, timeInForce, orderType,
                          limitType, instrument.idinstrument, instrument.lotsize, 1001, expiration);
        }

        // Prie and quantity check
        if (order.validatePrice(instrument) && order.validateQuantity(instrument)) {
            std::cout << "Order is validated for instrument " << order.idinstrument << ". Order is added in the orderbook.\n";
            orderBook.addOrder(order);
        } else {
            std::cout << "Order is not valid for the instrument " << order.idinstrument << ".\n";
        }
    }

    // Printing the orderbook
    orderBook.displayOrderBook();



    return 0;
}
