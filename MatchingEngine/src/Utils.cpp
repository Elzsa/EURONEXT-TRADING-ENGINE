#include "Utils.hpp"

bool isUniqueInstrument(const std::set<std::tuple<int, std::string, std::string>>& instrumentSet,
                        const Instrument& instrument)
{
    return instrumentSet.find(std::make_tuple(instrument.idinstrument, instrument.marketIdentificationCode,
                                              instrument.tradingCurrency)) == instrumentSet.end();
}

bool addInstrument(std::set<std::tuple<int, std::string, std::string>>& instrumentSet,
                   const Instrument& instrument)
{
    if (isUniqueInstrument(instrumentSet, instrument))
    {
        instrumentSet.insert(std::make_tuple(instrument.idinstrument, instrument.marketIdentificationCode,
                                             instrument.tradingCurrency));
        return true; // Instrument is added
    }
    return false; //  Instrument already exist
}
