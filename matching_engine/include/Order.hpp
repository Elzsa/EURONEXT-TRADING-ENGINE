#ifndef ORDER_HPP
#define ORDER_HPP

#include <chrono>
#include <string>
#include "Instrument.hpp"

// Enumeration for TimeInForce (order validity type)
enum class TimeInForce {
    GTD,         // Good Till Date
    DAY          // Order that is always valid
};

// Enumeration for OrderType (type of order)
enum class OrderType {
    BID,         // Buy Order
    ASK          // Sell Order
};

enum class LimitType {
    LIMIT,
    NONE
};

// Order class definition
class Order {
public:
    // Attributes (aligned with the database structure)
    int idorder;  // Unique ID of the order
    std::string marketIdentificationCode; // Market Identification Code (MIC)
    std::string tradingCurrency;          // Trading currency
    std::chrono::system_clock::time_point priority; // Priority timestamp, it goes to nanoseconds
    double price;    // Price of the order
    int quantity; // Quantity requested
    TimeInForce timeinforce; // Validity type of the order (e.g., GTD)
    OrderType ordertype;     // Type of order (BID or ASK)
    LimitType limitType;
    int idinstrument;        // Instrument ID
    int originalqty;         // Original quantity of the order
    int idfirm;              // Firm ID submitting the order
    std::chrono::system_clock::time_point expirationDate; // only for GTD

    // Constructor for GTD orders
    Order(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency,
          std::chrono::system_clock::time_point priority, double price, int quantity,
          TimeInForce timeinforce, OrderType ordertype, LimitType limitType, int idinstrument, int originalqty, int idfirm,
          std::chrono::system_clock::time_point expirationDate);

    // Constructor for DAY orders (without expiration date)
    Order(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency,
          std::chrono::system_clock::time_point priority, double price, int quantity,
          TimeInForce timeinforce, OrderType ordertype, LimitType limitType, int idinstrument, int originalqty, int idfirm);

    // Display order details
    void display() const;

    // CHECK if order's price is ok (positive and a multiple of pricedecimal attribute)
    bool validatePrice(const Instrument& instrument) const;

    // CHECK if order's quantity is positive and a multiple of lotsize attribute
    bool validateQuantity(const Instrument& instrument) const;

};

#endif // ORDER_HPP
