#include "InstrumentManager.hpp"
#include <iostream>

bool InstrumentManager::addInstrument(const Instrument& instrument) {
    if (isUniqueInstrument(instrumentSet, instrument)) {
        instrumentSet.insert(std::make_tuple(instrument.idinstrument, instrument.marketIdentificationCode,
                                             instrument.tradingCurrency));
        instruments.push_back(instrument);
        std::cout << "Instrument added : " << instrument.idinstrument << "\n";
        return true;
    } else {
        std::cout << "Instrument already existing\n";
        return false;
    }
}

const std::vector<Instrument>& InstrumentManager::getInstruments() const {
    return instruments;
}
