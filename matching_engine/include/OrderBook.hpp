//
// Created by PAYA Elsa on 08/01/2025.
//
#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include <map>
#include <deque>
#include <iostream>
#include "Order.hpp"

// OrderBook for managing both BID and ASK orders
class OrderBook {
public:
    // Maps for storing orders, key is price which is the double, value is the list of orders at that price
    std::map<double, std::deque<Order>> bidOrders;  // Orders to buy (BID)
    std::map<double, std::deque<Order>> askOrders;  // Orders to sell (ASK)

    // Constructor
    OrderBook();

    // Method to insert a new order into the order book
    void addOrder(const Order& order);

    // Remove an order from the order book based on idorder, marketIdentificationCode, and tradingCurrency
    void removeOrder(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency, OrderType orderType);


    // Method to display the OrderBook (BID and ASK)
    void displayOrderBook() const;

    // Method to display a specific order located in the OrderBook using its 3 primary keys
    void displayOrder(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency) const;

};

#endif // ORDERBOOK_HPP
