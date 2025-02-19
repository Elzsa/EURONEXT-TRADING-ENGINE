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
    std::cout << "\n\n============== ORDER BOOK ==============\n";

    std::cout << "\n\nBID Orders=====================\n";
    for (const auto& bid : bidOrders) {
        std::cout << "Price LEVEL: " << bid.first << "\n";
        for (const auto& order : bid.second) {
            order.display();
        }
    }

    std::cout << "\n\nASK Orders=====================\n";
    for (const auto& ask : askOrders) {
        std::cout << "Price LEVEL: " << ask.first << "\n";
        for (const auto& order : ask.second) {
            order.display();
        }
    }

    std::cout << "\n\n============== END OF ORDER BOOK ==============\n";
}


void OrderBook::displayOrder(int idorder, const std::string& marketIdentificationCode, const std::string& tradingCurrency) const {
    // Search first in BID
    for (const auto& bid : bidOrders) {
        for (const auto& order : bid.second) {
            if (order.idorder == idorder &&
                order.marketIdentificationCode == marketIdentificationCode &&
                order.tradingCurrency == tradingCurrency) {
                order.display(); // Affiche l'ordre trouvé
                return; // Si trouvé, on quitte la fonction
                }
        }
    }

    // Search secondly in ASK if not in BID
    for (const auto& ask : askOrders) {
        for (const auto& order : ask.second) {
            if (order.idorder == idorder &&
                order.marketIdentificationCode == marketIdentificationCode &&
                order.tradingCurrency == tradingCurrency) {
                order.display(); // Affiche l'ordre trouvé
                return; // Si trouvé, on quitte la fonction
                }
        }
    }

    std::cout << "Order not found in the orderbook.\n"; // Message si l'ordre n'est pas trouvé dans l'OrderBook
}



