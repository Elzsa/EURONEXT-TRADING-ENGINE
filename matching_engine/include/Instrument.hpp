//
// Created by PAYA Elsa on 08/01/2025.
//
#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include <string>

enum class State {
    ACTIVE,
    INACTIVE,
    SUSPENDED,
    DELISTED
    // Diferrent states for our order
};

//  POC Efrei ppt p.4
class Instrument {
public:
    int idinstrument;   // ISIN code
    std::string marketIdentificationCode; // Market Identification Code (MIC)
    std::string tradingCurrency;          // Trading currency
    char name[50];           // Instrument name (max 50 cara) mentionend in POC
    int issue;
    State state;
    double  refprice;          // the price is a double
    int idtradinggroup;
    int lotsize;
    int pricedecimal;
    int currentorderid;
    int currenttradeid;
    int idapf;


    Instrument(int idinstrument, const std::string& marketIdentificationCode, const std::string& tradingCurrency,
    const std::string& name, int issue, State state, double refprice, int idtradinggroup,
    int lotsize, int pricedecimal, int currentorderid, int currenttradeid, int idapf);


    void display() const;
};

#endif

