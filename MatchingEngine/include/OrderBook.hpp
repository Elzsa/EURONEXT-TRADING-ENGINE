// OrderBook.hpp

#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include "Order.hpp"

// Structure to represent a trade that occurs when orders match
struct Trade
{
    int tradeId;
    int buyOrderId;
    int sellOrderId;
    std::string marketIdentificationCode;
    std::string tradingCurrency;
    double price;
    int quantity;
    std::chrono::system_clock::time_point timestamp;

    void display() const;
};

// OrderBook for managing both BID and ASK orders
class OrderBook
{
private:
    int nextTradeId;
    std::vector<Trade> trades;
    void cleanupExecutedOrders();

public:
    // Maps for storing orders, key is price which is the double, value is the list of orders at that price
    // For BID orders, we use reverse ordering to prioritize higher prices first
    std::map<double, std::deque<Order>, std::greater<double>> bidOrders; // Orders to buy (BID)
    // For ASK orders, we use normal ordering to prioritize lower prices first
    std::map<double, std::deque<Order>> askOrders; // Orders to sell (ASK)

    // Constructor
    OrderBook();

    // Method to insert a new order into the order book
    void addOrder(const Order& order);

    // Match orders according to Price-Time Priority algorithm
    // Returns the number of trades executed
    int matchOrders();

    // Remove an order from the order book based on idorder, marketIdentificationCode, and tradingCurrency
    void removeOrder(int idorder, const std::string& marketIdentificationCode,
                     const std::string& tradingCurrency, OrderType orderType);

    // Method to display the OrderBook (BID and ASK)
    void displayOrderBook() const;

    // Method to display a specific order located in the OrderBook using its 3 primary keys
    void displayOrder(int idorder, const std::string& marketIdentificationCode,
                      const std::string& tradingCurrency) const;

    // Method to display all trades that have occurred
    void displayTrades() const;
};

#endif // ORDERBOOK_HPP
