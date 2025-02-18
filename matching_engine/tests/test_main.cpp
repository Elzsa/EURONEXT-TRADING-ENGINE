#include <iostream>
#include <chrono>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"

int main() {

    // Création d'un instrument
    Instrument instrument1(1, "XPAR",  "EUR",
        "AAPL", 20220101, State::ACTIVE, 150, 1001, 100,
        2, 1, 1, 2022);

    Instrument instrument2(2, "XPAR",  "EUR",
        "MSFT", 20220102, State::ACTIVE, 200, 1002, 400,
        1, 2, 2, 2023);

    instrument1.display();
    instrument2.display();
    // ORDRES

    auto now = std::chrono::system_clock::now();

    // Créer un ordre GTD (ASK) avec une expiration dans 5 jours
    auto ext1 = now + std::chrono::hours(24 * 5);
    Order gtdOrder(101, instrument1.marketIdentificationCode, instrument1.tradingCurrency,
        std::chrono::system_clock::now(), instrument1.refprice, instrument1.lotsize,
        TimeInForce::GTD, OrderType::ASK, instrument1.idinstrument, instrument1.lotsize, 1001,
        ext1);

    // Créer un ordre LIMIT (ASK)
    auto ext1_limit = now + std::chrono::hours(24 * 0);
    Order limitOrder(102, instrument1.marketIdentificationCode, instrument1.tradingCurrency,
        std::chrono::system_clock::now(), instrument2.refprice, instrument2.lotsize,
        TimeInForce::LIMIT, OrderType::ASK, instrument2.idinstrument, instrument2.lotsize, 1001, ext1_limit);

    // TESTS
    // 1. Tester si l'ordre GTD est actif
    std::cout << "\n===== Testing GTD Order =====\n";
    gtdOrder.display();
    if (gtdOrder.isExpired(now)) {
        std::cout << "GTD Order has expired.\n";
    } else {
        std::cout << "GTD Order is still active.\n";
    }

    // Simuler l'avancement du temps (25 heures plus tard)
    auto futureTime = now + std::chrono::hours(25*5);
    std::cout << "\nSimulating 25 hours later...\n";
    if (gtdOrder.isExpired(futureTime)) {
        std::cout << "GTD Order has expired after 25 hours.\n";
    } else {
        std::cout << "GTD Order is still active after 25 hours.\n";
    }

    // 2. Tester un Limit Order
    std::cout << "\n===== Testing Limit Order =====\n";
    limitOrder.display();

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
