#include <iostream>
#include <chrono>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"
#include "../include/OrderBook.hpp"
#include "../include/Utils.hpp"

int main() {

    // Création d'un OrderBook
    OrderBook orderBook;

    // Création d'un instrument
    Instrument instrument1(1, "XPAR",  "EUR",
        "AAPL", 20220101, State::ACTIVE, 150, 1001, 100,
        2, 1, 1, 2022);

    Instrument instrument2(2, "XPAR",  "EUR",
        "MSFT", 20220102, State::ACTIVE, 2740.01, 1002, 400,
        2, 2, 2, 2023);

    //instrument1.display();
    //instrument2.display();

    // ORDRES
    auto now = std::chrono::system_clock::now();

    // Créer un ordre GTD (ASK) avec une expiration dans 5 jours
    auto ext1 = now + std::chrono::hours(24 * 5);
    Order gtdOrder(instrument1.idinstrument, instrument1.marketIdentificationCode, instrument1.tradingCurrency,
        std::chrono::system_clock::now(), instrument1.refprice, instrument1.lotsize,
        TimeInForce::GTD, OrderType::ASK, LimitType::LIMIT, instrument1.idinstrument, instrument1.lotsize, 1001,
        ext1);

    // Créer un ordre LIMIT (ASK) avec une expiration immédiate (DAY)
    Order limitOrder(instrument2.idinstrument, instrument2.marketIdentificationCode, instrument2.tradingCurrency,
        std::chrono::system_clock::now(), instrument2.refprice, 800,
        TimeInForce::DAY, OrderType::ASK, LimitType::LIMIT, instrument2.idinstrument, instrument2.lotsize, 1001);

    // Affichage des ordres
    gtdOrder.display();
    limitOrder.display();


    /////////////////////////// ORDER VALIDITY
    if (limitOrder.validatePrice(instrument2) && limitOrder.validateQuantity(instrument2)) {
        std::cout << "L'ordre est valide.\n";
    } else {
        std::cout << "L'ordre n'est pas valide.\n";
    }

    // Add orders in OrderBook
    orderBook.addOrder(gtdOrder);
    orderBook.addOrder(limitOrder);

    // Display orders in OrderBook
    orderBook.displayOrderBook();

    // Suppressing the order with id equal to 101
    orderBook.removeOrder(101, instrument1.marketIdentificationCode, instrument1.tradingCurrency, OrderType::ASK);


    std::cout << "\nAfter suppression of order 101 :\n";
    orderBook.displayOrderBook();


    std::cout << "\nSearch order with id 102, market 'XPAR', currency 'EUR' :\n";
    orderBook.displayOrder(102, instrument2.marketIdentificationCode, instrument2.tradingCurrency);

    std::cout << "\nSearch order with id 101, market 'XPAR', currency 'EUR' :\n";
    orderBook.displayOrder(101, instrument1.marketIdentificationCode, instrument1.tradingCurrency);


    // 2. Tester un Limit Order
    //std::cout << "\n===== Testing Limit Order =====\n";
    //limitOrder.display();

    // Créer un ordre ASK pour tester le limit order (vente à 250)
    //Order askOrder(103, now, 250, 30, TimeInForce::LIMIT, OrderType::ASK, instrument1.idinstrument, 30, 1003);

    //std::cout << "\nSimulating Limit Order Matching...\n";
    /*if (limitOrder.price >= askOrder.price) {
        int executedQuantity = std::min(limitOrder.quantity, askOrder.quantity); // Quantité échangée
        std::cout << "Transaction executed:\n";
        std::cout << "Price: " << askOrder.price << ", Quantity: " << executedQuantity << "\n";

        // Réduire les quantités restantes
        limitOrder.quantity -= executedQuantity;
        askOrder.quantity -= executedQuantity;

        std::cout << "Remaining BID quantity: " << limitOrder.quantity << "\n";
        std::cout << "Remaining ASK quantity: " << askOrder.quantity << "\n";
    } else {
        std::cout << "No transaction possible. BID price: " << limitOrder.price
                  << ", ASK price: " << askOrder.price << ".\n";
    }*/

    return 0;
}
