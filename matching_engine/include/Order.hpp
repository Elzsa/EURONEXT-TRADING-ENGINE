#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <chrono>
#include <optional>
#include <iostream>

// Enumeration for TimeInForce (order validity type)
enum class TimeInForce {
    GTD,         // Good Till Date
    DAY          // Valid for the trading day
};

// Enumeration for OrderType (type of order)
enum class OrderType {
    BID,         // Buy Order
    ASK          // Sell Order
};

// Order class definition
class Order {
public:
    // Attributes (aligned with the database structure)
    int idorder;  // Unique ID of the order
    std::chrono::system_clock::time_point priority; // Priority timestamp
    int price;    // Price of the order
    int quantity; // Quantity requested
    TimeInForce timeinforce; // Validity type of the order (e.g., GTD)
    OrderType ordertype;     // Type of order (BID or ASK)
    int idinstrument;        // Instrument ID
    int originalqty;         // Original quantity of the order
    int idfirm;              // Firm ID submitting the order

    // Constructor
    Order(int idorder, std::chrono::system_clock::time_point priority, int price, int quantity,
          TimeInForce timeinforce, OrderType ordertype, int idinstrument, int originalqty, int idfirm);

    // Display order details
    void display() const;

    // Validate limit order (price must be strictly positive)
    bool isValidLimitOrder() const;

    // Check if the order is expired (for GTD orders)
    bool isExpired(const std::chrono::system_clock::time_point& current_time) const;
};

#endif // ORDER_HPP
