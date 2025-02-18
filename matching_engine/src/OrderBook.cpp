//
// Created by PAYA Elsa on 08/01/2025.
//
#include "OrderBook.hpp"

// Constructor
OrderBook::OrderBook() {}

void OrderBook::addOrder(const Order& order) {
    // Insert BID orders into bidOrders map
    if (order.ordertype == OrderType::BID) {
        bidOrders[order.price].push_back(order);
    }
    // Insert ASK orders into askOrders map
    else if (order.ordertype == OrderType::ASK) {
        askOrders[order.price].push_back(order);
    }
}

// Remove an order from the order book based on idorder, marketIdentificationCode, and tradingCurrency
void OrderBook::removeOrder(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency, OrderType orderType) {
    // Determine the appropriate map based on order type (BID or ASK)
    if (orderType == OrderType::BID) {
        // Search and remove from bid orders
        for (auto it = bidOrders.begin(); it != bidOrders.end(); ++it) {
            auto& ordersAtPrice = it->second;
            for (auto orderIt = ordersAtPrice.begin(); orderIt != ordersAtPrice.end(); ++orderIt) {
                if (orderIt->idorder == idorder &&
                    orderIt->marketIdentificationCode == marketIdentificationCode &&
                    orderIt->tradingCurrency == tradingCurrency) {
                    ordersAtPrice.erase(orderIt);
                    return;
                    }
            }
        }
    }
    else if (orderType == OrderType::ASK) {
        // Search and remove from ask orders
        for (auto it = askOrders.begin(); it != askOrders.end(); ++it) {
            auto& ordersAtPrice = it->second;
            for (auto orderIt = ordersAtPrice.begin(); orderIt != ordersAtPrice.end(); ++orderIt) {
                if (orderIt->idorder == idorder &&
                    orderIt->marketIdentificationCode == marketIdentificationCode &&
                    orderIt->tradingCurrency == tradingCurrency) {
                    ordersAtPrice.erase(orderIt);
                    return;
                    }
            }
        }
    }
}



// Display all orders in the order book
void OrderBook::displayOrderBook() const {
    std::cout << "======= Order Book =======\n";

    std::cout << "\nBID Orders:\n";
    for (const auto& bid : bidOrders) {
        std::cout << "Price: " << bid.first << "\n";
        for (const auto& order : bid.second) {
            order.display();
        }
    }

    std::cout << "\nASK Orders:\n";
    for (const auto& ask : askOrders) {
        std::cout << "Price: " << ask.first << "\n";
        for (const auto& order : ask.second) {
            order.display();
        }
    }

    std::cout << "==========================\n";
}


