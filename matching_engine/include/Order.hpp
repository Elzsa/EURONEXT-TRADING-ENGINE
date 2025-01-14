//
// Created by PAYA Elsa on 08/01/2025.
//

// include/Order.hpp
#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <chrono>
#include <ctime>
#include "Instrument.hpp"

// Définition des énumérations pour TimeInForce et OrderType
enum class TimeInForce {
    DAY,         // Valide pour la journée
    GTC,         // Good Till Cancelled
    GTD          // Good Till Date
    // Ajouter le limit order page 7 POC Euronext
};

enum class OrderType {
    BID,       // Ordre
    ASK,       // Ordre
};

// Classe représentant un ordre
class Order {
public:
    int idorder;               // ID de l'ordre
    std::chrono::system_clock::time_point priority; // Horodatage de la priorité
    int price;                 // Prix de l'ordre
    int quantity;             // Quantité demandée
    TimeInForce timeinforce;  // Type de validité de l'ordre
    OrderType ordertype;      // Type d'ordre (limite ou marché)
    int idinstrument;         // ID de l'instrument concerné
    int originalqty;          // Quantité originale de l'ordre
    int idfirm;               // ID de la firme émettrice de l'ordre

    // Constructeur
    Order(int idorder, std::chrono::system_clock::time_point priority, int price, int quantity,
          TimeInForce timeinforce, OrderType ordertype, int idinstrument, int originalqty, int idfirm);

    // Méthode pour afficher les informations de l'ordre
    void display() const;
};

#endif
