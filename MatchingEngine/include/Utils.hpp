#ifndef UTILS_HPP
#define UTILS_HPP

#include <set>
#include "Instrument.hpp"

// Verify if isntrument has unique id
bool isUniqueInstrument(const std::set<std::tuple<int, std::string, std::string>>& instrumentSet,
                        const Instrument& instrument);

// Add instrument in set if isUniqueInstrument() is true
bool addInstrument(std::set<std::tuple<int, std::string, std::string>>& instrumentSet,
                   const Instrument& instrument);

#endif // UTILS_HPP
