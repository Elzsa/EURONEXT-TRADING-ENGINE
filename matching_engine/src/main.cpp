//
// Created by PAYA Elsa on 08/01/2025.
//

#include <iostream>
#include <set>
#include <chrono>
#include "../include/Instrument.hpp"
#include "../include/Order.hpp"
#include "../include/OrderBook.hpp"
#include "../include/Utils.hpp"
#include "../include/InstrumentManager.hpp"

int main() {

    // OrderBook creation
    OrderBook orderBook;
    // set to check unicity of instrument'id triplet (idinstrument, marketIdentificationCode and tradingCurrency)
    std::set<std::tuple<int, std::string, std::string>> instrumentSet;
    // Gestionnaire d'instruments
    InstrumentManager instrumentManager;

    // Création et ajout d'instruments
    instrumentManager.addInstrument(Instrument(1, "XPAR", "EUR", "AAPL", 20220101, State::ACTIVE,
                                               150, 1001, 100, 2, 1, 1, 2022));
    instrumentManager.addInstrument(Instrument(2, "XPAR", "EUR", "MSFT", 20220102, State::ACTIVE,
                                               2740.01, 1002, 400, 2, 2, 2, 2023));
    instrumentManager.addInstrument(Instrument(1, "XPAR", "EUR", "AAPL", 20220101, State::ACTIVE,
                                               150, 1001, 100, 2, 1, 1, 2022)); // Doublon


    // Récupération des instruments
    const auto& instruments = instrumentManager.getInstruments();



    return 0;
}
