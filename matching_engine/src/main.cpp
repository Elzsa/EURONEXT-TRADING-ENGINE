//
// Created by PAYA Elsa on 08/01/2025.
//

// src/main.cpp
#include <iostream>
#include "Instrument.hpp"

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

    return 0;
}
