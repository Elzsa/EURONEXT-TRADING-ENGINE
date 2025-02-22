#ifndef INSTRUMENT_MANAGER_HPP
#define INSTRUMENT_MANAGER_HPP

#include <set>
#include <vector>
#include "Instrument.hpp"
#include "Utils.hpp"

class InstrumentManager {
private:
    std::set<std::tuple<int, std::string, std::string>> instrumentSet; // store each valid instrument'ids
    std::vector<Instrument> instruments; // Store every valid instrument

public:
    // We verify unicity and we add the instrument
    bool addInstrument(const Instrument& instrument);

    // return list of instruments
    const std::vector<Instrument>& getInstruments() const;
};

#endif // INSTRUMENT_MANAGER_HPP
