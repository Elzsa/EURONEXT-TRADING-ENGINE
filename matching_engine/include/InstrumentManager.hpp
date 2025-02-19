#ifndef INSTRUMENT_MANAGER_HPP
#define INSTRUMENT_MANAGER_HPP

#include <set>
#include <vector>
#include "Instrument.hpp"
#include "Utils.hpp"

class InstrumentManager {
private:
    std::set<std::tuple<int, std::string, std::string>> instrumentSet;
    std::vector<Instrument> instruments; // Stocke tous les instruments créés

public:
    // Ajoute un instrument et vérifie l'unicité
    bool addInstrument(const Instrument& instrument);

    // Retourne la liste des instruments
    const std::vector<Instrument>& getInstruments() const;
};

#endif // INSTRUMENT_MANAGER_HPP
