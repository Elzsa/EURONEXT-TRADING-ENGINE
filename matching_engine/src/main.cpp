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
    // Créer un instrument
     Instrument instrument1(1, "AAPL", 20220101, State::ACTIVE, 150, 1001, 100, 2, 1, 1, 2022);
    // Afficher les informations de chaque instrument
    instrument1.display();
    // Créer des ordres
    auto now = std::chrono::system_clock::now();
    Order order1(101, now, 150, 100, TimeInForce::DAY, OrderType::LIMIT, instrument1.idinstrument, 100, 1001);
    // Afficher les informations des ordres
    order1.display();

    return 0;
}
