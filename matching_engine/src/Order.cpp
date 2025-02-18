#include "Order.hpp"
#include <iomanip>
#include <ctime>
#include <iostream>

// Constructor for GTD orders
Order::Order(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency,
    std::chrono::system_clock::time_point priority, int price, int quantity,
    TimeInForce timeinforce, OrderType ordertype, LimitType limitType,  int idinstrument, int originalqty, int idfirm,
    std::chrono::system_clock::time_point expirationDate)
    : idorder(idorder), marketIdentificationCode(marketIdentificationCode), tradingCurrency(tradingCurrency),priority(priority), price(price), quantity(quantity), timeinforce(timeinforce),
      ordertype(ordertype), limitType(limitType), idinstrument(idinstrument), originalqty(originalqty), idfirm(idfirm), expirationDate(expirationDate){}

// Constructor for DAY orders (no expirationDate)
Order::Order(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency,
    std::chrono::system_clock::time_point priority, int price, int quantity,
    TimeInForce timeinforce, OrderType ordertype, LimitType limitType, int idinstrument, int originalqty, int idfirm)
    : idorder(idorder), marketIdentificationCode(marketIdentificationCode), tradingCurrency(tradingCurrency),
      priority(priority), price(price), quantity(quantity), timeinforce(timeinforce), ordertype(ordertype),
      limitType(limitType), idinstrument(idinstrument), originalqty(originalqty), idfirm(idfirm) {
    // Default expirationDate for DAY orders (not used)
    expirationDate = std::chrono::system_clock::time_point{};
}



// Display order details
void Order::display() const {
    std::time_t priority_time = std::chrono::system_clock::to_time_t(priority);
    std::cout << "====== Order Information =======\n";
    std::cout << "Order ID: " << idorder << "\n";
    std::cout << "Market Identification Code (MIC): " << marketIdentificationCode << "\n";
    std::cout << "Trading Currency: " << tradingCurrency << "\n";
    std::cout << "Priority: " << std::ctime(&priority_time);
    std::cout << "Price: " << price << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Time In Force: " << (timeinforce == TimeInForce::GTD ? "GTD" : "DAY") << "\n";
    std::cout << "Order Type: " << (ordertype == OrderType::BID ? "BID" : "ASK") << "\n";
    std::cout << "Instrument ID: " << idinstrument << "\n";
    std::cout << "Original Quantity: " << originalqty << "\n";
    std::cout << "Firm ID: " << idfirm << "\n";
    // Display expiration date only if GTD
    if (timeinforce == TimeInForce::GTD) {
        std::time_t expTime = std::chrono::system_clock::to_time_t(expirationDate);
        std::cout << "Expiration Date: " << std::ctime(&expTime);
    } else {
        std::cout << "Expiration Date: N/A (DAY order)\n";
    }

    std::cout << "================================\n";
}
