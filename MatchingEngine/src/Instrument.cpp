#include "Instrument.hpp"
#include <iostream>
#include <cstring>

Instrument::Instrument(int idinstrument, const std::string& marketIdentificationCode,
                       const std::string& tradingCurrency, const std::string& name,
                       int issue, State state, double refprice, int idtradinggroup,
                       int lotsize, int pricedecimal, int currentorderid, int currenttradeid, int idapf)
    : idinstrument(idinstrument), marketIdentificationCode(marketIdentificationCode), tradingCurrency(tradingCurrency),
      issue(issue), state(state), refprice(refprice), idtradinggroup(idtradinggroup),
      lotsize(lotsize), pricedecimal(pricedecimal), currentorderid(currentorderid), currenttradeid(currenttradeid),
      idapf(idapf)
{
    strncpy(this->name, name.c_str(), sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0'; // Name is null-terminated
}

void Instrument::display() const
{
    std::cout << "Instrument ID: " << idinstrument << "\n";
    std::cout << "Market Identification Code (MIC): " << marketIdentificationCode << "\n";
    std::cout << "Trading Currency: " << tradingCurrency << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Issue: " << issue << "\n";
    std::cout << "State: " << (state == State::ACTIVE
                                   ? "ACTIVE"
                                   : state == State::INACTIVE
                                   ? "INACTIVE"
                                   : state == State::SUSPENDED
                                   ? "SUSPENDED"
                                   : "DELISTED") << "\n";
    std::cout << "Reference Price: " << refprice << "\n";
    std::cout << "Trading Group ID: " << idtradinggroup << "\n";
    std::cout << "Lot Size: " << lotsize << "\n";
    std::cout << "Price Decimal: " << pricedecimal << "\n";
    std::cout << "Current Order ID: " << currentorderid << "\n";
    std::cout << "Current Trade ID: " << currenttradeid << "\n";
    std::cout << "APF ID: " << idapf << "\n";
    std::cout << "================================ " << "\n";
}
