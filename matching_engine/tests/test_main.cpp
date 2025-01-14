//
// Created by PAYA Elsa on 08/01/2025.
//

#include <iostream>
#include <chrono>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"
#include "../include/OrderBook.hpp"


int main() {
    // INSTRUMENTS
    // Créer un instrument
    Instrument instrument1(1, "AAPL", 20220101, State::ACTIVE, 150, 1001, 100, 2, 1, 1, 2022);
    Instrument instrument2(2, "GOOGL", 20220102, State::INACTIVE, 2800, 1002, 50, 2, 2, 2, 2023);
    Instrument instrument3(3, "AMZN", 20220103, State::SUSPENDED, 3400, 1003, 200, 2, 3, 3, 2024);
    Instrument instrument4(4, "TSLA", 20220104, State::DELISTED, 750, 1004, 100, 2, 4, 4, 2025);
    Instrument instrument5(5, "MSFT", 20220105, State::ACTIVE, 299, 1005, 100, 2, 5, 5, 2026);
    Instrument instrument6(6, "NFLX", 20220106, State::INACTIVE, 650, 1006, 50, 2, 6, 6, 2027);
    Instrument instrument7(7, "NVDIA", 20220107, State::ACTIVE, 650, 1007, 150, 2, 7, 7, 2027);
    Instrument instrument8(8, "AAPL", 20220108, State::ACTIVE, 2800, 1008, 2000, 2, 8, 8, 2027);
    Instrument instrument9(9, "AAA", 20220109, State::ACTIVE, 3400, 1009, 24, 2, 9, 9, 2027);
    Instrument instrument10(10, "BBB", 20220110, State::ACTIVE, 299, 1010, 157, 2, 10, 10, 2026);

    // Afficher les informations de chaque instrument
    instrument1.display();
    instrument2.display();
    instrument3.display();
    instrument4.display();
    instrument5.display();
    instrument6.display();

    // Créer des ordres
    auto now = std::chrono::system_clock::now();
    Order order1(101, now, 150, 100, TimeInForce::DAY, OrderType::BID, instrument1.idinstrument, 100, 1001);
    Order order2(102, now, 2800, 50, TimeInForce::GTC, OrderType::BID, instrument2.idinstrument, 50, 1002);
    Order order3(103, now, 3400, 150, TimeInForce::DAY, OrderType::ASK, instrument3.idinstrument, 150, 1003);
    Order order4(104, now, 750, 80, TimeInForce::GTD, OrderType::ASK, instrument4.idinstrument, 80, 1004);
    Order order5(105, now, 299, 120, TimeInForce::GTC, OrderType::ASK, instrument5.idinstrument, 120, 1005);
    Order order6(106, now, 650, 60, TimeInForce::DAY, OrderType::BID, instrument6.idinstrument, 60, 1006);
    Order order7(107, now, 650, 10, TimeInForce::DAY, OrderType::BID, instrument7.idinstrument, 60, 1007);
    Order order8(108, now, 2800, 20, TimeInForce::GTD, OrderType::BID, instrument8.idinstrument, 60, 1008);
    Order order9(109, now, 3400, 14, TimeInForce::DAY, OrderType::ASK, instrument9.idinstrument, 60, 1009);
    Order order10(110, now, 299, 1, TimeInForce::DAY, OrderType::ASK, instrument10.idinstrument, 60, 1010);


    // Afficher les informations des ordres
    order1.display();
    order2.display();
    order1.display();
    order2.display();
    order3.display();
    order4.display();
    order5.display();
    order6.display();

    OrderBook orderBook;
    // Ajouter dans l'orderbook les orders
    orderBook.addOrder(order1);
    orderBook.addOrder(order2);
    orderBook.addOrder(order3);
    orderBook.addOrder(order4);
    orderBook.addOrder(order5);
    orderBook.addOrder(order6);
    orderBook.addOrder(order7);
    orderBook.addOrder(order8);
    orderBook.addOrder(order9);
    orderBook.addOrder(order10);

    // Afficher l'ordre book
    orderBook.display2();

    // Obtenir le top of the book
    auto [topBid, topAsk] = orderBook.getTopOfBook();
    std::cout << "Top Bid: " << topBid.price << ", Top Ask: " << topAsk.price << std::endl;

}

