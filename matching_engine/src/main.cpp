//
// Created by PAYA Elsa on 08/01/2025.
//

// src/main.cpp
#include <iostream>
#include <chrono>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"

int main() {

    // INSTRUMENTS
     Instrument instrument1(1, "AAPL", 20220101, State::ACTIVE, 150, 1001, 100, 2, 1, 1, 2022);
    instrument1.display();

    auto now = std::chrono::system_clock::now();
    Order order1(101, now, 150, 100, TimeInForce::DAY, OrderType::BID, instrument1.idinstrument, 100, 1001);

    order1.display();

    return 0;
}
