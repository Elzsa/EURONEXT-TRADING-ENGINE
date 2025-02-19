#include "Order.hpp"
#include "Instrument.hpp"

#include <cmath>
#include <iomanip>
#include <ctime>
#include <iostream>

// Implémentation du constructeur par défaut
Order::Order() : idorder(0), marketIdentificationCode(""), tradingCurrency(""),
                 priority(std::chrono::system_clock::now()), price(0.0), quantity(0),
                 timeinforce(TimeInForce::DAY), ordertype(OrderType::BID),
                 limitType(LimitType::LIMIT), idinstrument(0), originalqty(0), idfirm(0),
                 expirationDate(std::chrono::system_clock::now()) {}



// Constructor for GTD orders
Order::Order(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency,
    std::chrono::system_clock::time_point priority, double price, int quantity,
    TimeInForce timeinforce, OrderType ordertype, LimitType limitType,  int idinstrument, int originalqty, int idfirm,
    std::chrono::system_clock::time_point expirationDate)
    : idorder(idorder), marketIdentificationCode(marketIdentificationCode), tradingCurrency(tradingCurrency),priority(priority), price(price), quantity(quantity), timeinforce(timeinforce),
      ordertype(ordertype), limitType(limitType), idinstrument(idinstrument), originalqty(originalqty), idfirm(idfirm), expirationDate(expirationDate){}

// Constructor for DAY orders (no expirationDate)
Order::Order(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency,
    std::chrono::system_clock::time_point priority, double price, int quantity,
    TimeInForce timeinforce, OrderType ordertype, LimitType limitType, int idinstrument, int originalqty, int idfirm)
    : idorder(idorder), marketIdentificationCode(marketIdentificationCode), tradingCurrency(tradingCurrency),
      priority(priority), price(price), quantity(quantity), timeinforce(timeinforce), ordertype(ordertype),
      limitType(limitType), idinstrument(idinstrument), originalqty(originalqty), idfirm(idfirm) {
    // Default expirationDate for DAY orders (not used) N/A (DAY order)
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
    // Extract nanoseconds
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(priority.time_since_epoch()).count() % 1000000000;
    std::cout << "Priority Nanoseconds: " << ns << "\n";
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



bool Order::validatePrice(const Instrument& instrument) const {
    if (price <= 0) {
        std::cout << "ERROR: Price must be strictly positive.\n";
        return false;
    }


    double precision = std::pow(10, instrument.pricedecimal);
    double remainder = std::fmod(price * precision, 1.0);
    double tolerance = 1e-8;
    if (std::fabs(remainder) > tolerance) {
        std::cout << "ERROR: Price must be a multiple of the instrument's pricedecimal.\n";
        return false;
    }

    return true;
}

// Quantity validation
bool Order::validateQuantity(const Instrument& instrument) const {
    // Verify if quantity is positive
    if (quantity <= 0) {
        std::cout << "ERROR: QUantity must be strictly positive.\n";
        return false;
    }

    //as quantity is an int it is converted to an int thus decimal part is suppressed
    if (std::fmod(quantity, 1.0) != 0.0) {
        std::cout << "ERROR: Quantity must be an integer.\n";
        return false;
    }

    // Verify if quantity is a multiple of LOT SIZE
    if (quantity % instrument.lotsize != 0) {
        std::cout << "ERROR: Order quantity must be a multiple of its lot size.\n";
        return false;
    }

    return true;
}
