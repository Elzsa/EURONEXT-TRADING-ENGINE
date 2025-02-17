#include "Order.hpp"
#include <iomanip>
#include <ctime>

// Constructor implementation
Order::Order(int idorder, std::chrono::system_clock::time_point priority, int price, int quantity,
             TimeInForce timeinforce, OrderType ordertype, int idinstrument, int originalqty, int idfirm)
    : idorder(idorder), priority(priority), price(price), quantity(quantity), timeinforce(timeinforce),
      ordertype(ordertype), idinstrument(idinstrument), originalqty(originalqty), idfirm(idfirm) {}

// Display order details
void Order::display() const {
    std::time_t priority_time = std::chrono::system_clock::to_time_t(priority);
    std::cout << "====== Order Information =======\n";
    std::cout << "Order ID: " << idorder << "\n";
    std::cout << "Priority: " << std::ctime(&priority_time);
    std::cout << "Price: " << price << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Time In Force: " << (timeinforce == TimeInForce::GTD ? "GTD" : "DAY") << "\n";
    std::cout << "Order Type: " << (ordertype == OrderType::BID ? "BID" : "ASK") << "\n";
    std::cout << "Instrument ID: " << idinstrument << "\n";
    std::cout << "Original Quantity: " << originalqty << "\n";
    std::cout << "Firm ID: " << idfirm << "\n";
    std::cout << "================================\n";
}

// Validate limit order (price must be strictly positive)
bool Order::isValidLimitOrder() const {
    return price > 0;
}

// Check if the order is expired (for GTD orders)
bool Order::isExpired(const std::chrono::system_clock::time_point& current_time) const {
    return timeinforce == TimeInForce::GTD && priority < current_time;
}
