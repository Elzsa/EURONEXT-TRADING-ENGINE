#include <iostream>
#include <chrono>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"

int main() {
    // INSTRUMENTS
    // Création d'un instrument
    Instrument instrument1(1, "AAPL", 20220101, State::ACTIVE, 150, 1001, 100, 2, 1, 1, 2022);

    // ORDRES
    auto now = std::chrono::system_clock::now();

    // Créer un ordre GTD (ASK) avec une expiration dans 24 heures
    auto expirationTime = now + std::chrono::hours(24); // Expiration dans 24 heures
    Order gtdOrder(101, expirationTime, 300, 50, TimeInForce::GTD, OrderType::ASK, instrument1.idinstrument, 50, 1001);

    // Créer un limit order (BID) avec un prix maximum
    Order limitOrder(102, now, 300, 50, TimeInForce::DAY, OrderType::BID, instrument1.idinstrument, 50, 1002);

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
    auto futureTime = now + std::chrono::hours(25);
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
    Order askOrder(103, now, 250, 30, TimeInForce::DAY, OrderType::ASK, instrument1.idinstrument, 30, 1003);

    std::cout << "\nSimulating Limit Order Matching...\n";
    if (limitOrder.price >= askOrder.price) {
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
    }

    return 0;
}
