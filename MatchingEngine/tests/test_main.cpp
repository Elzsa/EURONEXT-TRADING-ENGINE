#include <iostream>
#include <chrono>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"
#include "../include/OrderBook.hpp"
#include "../include/Utils.hpp"

int main()
{
    // FICHIER BROUILLON POUR FAIRE DES PETITS TESTS


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
