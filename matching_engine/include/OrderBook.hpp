//
// Created by PAYA Elsa on 08/01/2025.
//
#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <map>
#include <queue>
#include <iostream>
#include "Order.hpp"

class OrderBook {
private:
    // Définitions des price levels pour les bids et asks
    using PriceLevel = std::queue<Order>; // FIFO pour les ordres à un même prix

    // Structures pour trier les price levels
    std::map<double, PriceLevel, std::greater<double>> bids; // Prix décroissants
    std::map<double, PriceLevel> asks;                      // Prix croissants

public:
    // Ajouter un ordre
    void addOrder(const Order& order);

    // Afficher l'order book
    void display() const;
    // Afficher l'order book
    void display2() const;

    // Obtenir le "top of the book" (le meilleur bid et ask)
    std::pair<Order, Order> getTopOfBook() const;
};

#endif // ORDER_BOOK_HPP
