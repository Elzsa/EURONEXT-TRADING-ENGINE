//
// Created by PAYA Elsa on 08/01/2025.
//
#include "OrderBook.hpp"


void OrderBook::addOrder(const Order& order) {
    if (order.ordertype == OrderType::BID) {
        bids[order.price].push(order);
    } else if (order.ordertype == OrderType::ASK) {
        asks[order.price].push(order);
    }
}

// Afficher l'ordre book : affichage basique de la forme Price Level: Prix | Orders: Nb d'ordres sur ce price level
void OrderBook::display() const {
    std::cout << "Order Book:\n";


    std::cout << "Bids (Highest to Lowest):" << std::endl;
    for (const auto& [price, level] : bids) {
        std::cout << "Price Level: " << price << " | Orders: " << level.size() << std::endl;
    }


    std::cout << "Asks (Lowest to Highest):" << std::endl;
    for (const auto& [price, level] : asks) {
        std::cout << "Price Level: " << price << " | Orders: " << level.size() << std::endl;
    }
}


void OrderBook::display2() const {
    std::cout << "Order Book:\n";

    std::cout << "Bids (Highest to Lowest):" << std::endl;
    for (const auto& [price, level] : bids) {
        std::cout << "Price Level: " << price << " | Orders: " << level.size() << std::endl;
        int timeLevel = 1;


        std::queue<Order> tempLevel = level;
        while (!tempLevel.empty()) {
            const Order& order = tempLevel.front();
            std::cout << "  Order: " << order.price << " (Time Level: " << timeLevel << ")" << std::endl;
            tempLevel.pop();  // Retirer l'élément de la queue
            timeLevel++;
        }
    }


    std::cout << "Asks (Lowest to Highest):" << std::endl;
    for (const auto& [price, level] : asks) {
        std::cout << "Price Level: " << price << " | Orders: " << level.size() << std::endl;
        int timeLevel = 1;


        std::queue<Order> tempLevel = level;
        while (!tempLevel.empty()) {
            const Order& order = tempLevel.front();
            std::cout << "  Order: " << order.price << " (Time Level: " << timeLevel << ")" << std::endl;
            tempLevel.pop();
            timeLevel++;
        }
    }
}



std::pair<Order, Order> OrderBook::getTopOfBook() const {
    Order topBid(0, std::chrono::system_clock::now(), 0, 0, TimeInForce::DAY, OrderType::BID, 0, 0, 0);
    Order topAsk(0, std::chrono::system_clock::now(), 0, 0, TimeInForce::DAY, OrderType::ASK, 0, 0, 0);

    if (!bids.empty()) {
        topBid = bids.begin()->second.front();
    }

    if (!asks.empty()) {
        topAsk = asks.begin()->second.front();
    }

    return {topBid, topAsk};
}
