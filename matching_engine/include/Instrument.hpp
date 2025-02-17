//
// Created by PAYA Elsa on 08/01/2025.
//

// include/Instrument.hpp
#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include <string>

enum class State {
    ACTIVE,
    INACTIVE,
    SUSPENDED,
    DELISTED
    // Etats possible de l'instrument via l'attribut state
};

// selon POC Efrei ppt p.4
class Instrument {
public:
    int idinstrument;
    char name[50];           // Nom de l'instrument (max 50 cara) selon POC EURO
    int issue;
    State state;             // Utilisation de l'énumération pour l'état
    int refprice;
    int idtradinggroup;
    int lotsize;
    int pricedecimal;
    int currentorderid;
    int currenttradeid;
    int idapf;


    Instrument(int idinstrument, const std::string& name, int issue, State state, int refprice, int idtradinggroup,
               int lotsize, int pricedecimal, int currentorderid, int currenttradeid, int idapf);


    void display() const;
};

#endif

