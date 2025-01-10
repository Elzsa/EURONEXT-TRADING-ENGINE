//
// Created by PAYA Elsa on 08/01/2025.
//

#include <iostream>
#include <chrono>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"


int main() {
    // INSTRUMENTS
    // Créer un instrument
    Instrument instrument1(1, "AAPL", 20220101, State::ACTIVE, 150, 1001, 100, 2, 1, 1, 2022);
    Instrument instrument2(2, "GOOGL", 20220102, State::INACTIVE, 2800, 1002, 50, 2, 2, 2, 2023);
    Instrument instrument3(3, "AMZN", 20220103, State::SUSPENDED, 3400, 1003, 200, 2, 3, 3, 2024);
    Instrument instrument4(4, "TSLA", 20220104, State::DELISTED, 750, 1004, 100, 2, 4, 4, 2025);
    Instrument instrument5(5, "MSFT", 20220105, State::ACTIVE, 299, 1005, 100, 2, 5, 5, 2026);
    Instrument instrument6(6, "NFLX", 20220106, State::INACTIVE, 650, 1006, 50, 2, 6, 6, 2027);

    // Afficher les informations de chaque instrument
    instrument1.display();
    instrument2.display();
    instrument3.display();
    instrument4.display();
    instrument5.display();
    instrument6.display();

    // Créer des ordres
    auto now = std::chrono::system_clock::now();
    Order order1(101, now, 150, 100, TimeInForce::DAY, OrderType::LIMIT, instrument1.idinstrument, 100, 1001);
    Order order2(102, now, 2800, 50, TimeInForce::GTC, OrderType::MARKET, instrument2.idinstrument, 50, 1002);
    Order order3(103, now, 3400, 150, TimeInForce::DAY, OrderType::LIMIT, instrument3.idinstrument, 150, 1003);
    Order order4(104, now, 750, 80, TimeInForce::GTD, OrderType::MARKET, instrument4.idinstrument, 80, 1004);
    Order order5(105, now, 299, 120, TimeInForce::GTC, OrderType::LIMIT, instrument5.idinstrument, 120, 1005);
    Order order6(106, now, 650, 60, TimeInForce::DAY, OrderType::LIMIT, instrument6.idinstrument, 60, 1006);


    // Afficher les informations des ordres
    order1.display();
    order2.display();
    order1.display();
    order2.display();
    order3.display();
    order4.display();
    order5.display();
    order6.display();
}

