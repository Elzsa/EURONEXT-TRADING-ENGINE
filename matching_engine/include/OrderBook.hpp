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

    using PriceLevel = std::queue<Order>;

    // Structures pour trier les price levels
    std::map<double, PriceLevel, std::greater<double>> bids;
    std::map<double, PriceLevel> asks;

public:

    void addOrder(const Order& order);


    void display() const;

    void display2() const;


    std::pair<Order, Order> getTopOfBook() const;
};

#endif // ORDER_BOOK_HPP
