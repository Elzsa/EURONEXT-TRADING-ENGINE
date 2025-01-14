//
// Created by PAYA Elsa on 08/01/2025.
//
// src/Order.cpp
#include "Order.hpp"
#include <iostream>

Order::Order(int idorder, std::chrono::system_clock::time_point priority, int price, int quantity,
             TimeInForce timeinforce, OrderType ordertype, int idinstrument, int originalqty, int idfirm)
    : idorder(idorder), priority(priority), price(price), quantity(quantity), timeinforce(timeinforce),
      ordertype(ordertype), idinstrument(idinstrument), originalqty(originalqty), idfirm(idfirm) {}

void Order::display() const {
    std::time_t priority_time = std::chrono::system_clock::to_time_t(priority);  // Convertir en temps lisible
    std::cout << "====== Order Information ======= \n";
    std::cout << "Order ID: " << idorder << "\n";
    std::cout << "Priority: " << std::ctime(&priority_time);  // Afficher l'heure d'entrée de l'ordre
    std::cout << "Price: " << price << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Time In Force: " << (timeinforce == TimeInForce::DAY ? "DAY" :
                                       timeinforce == TimeInForce::GTC ? "GTC" : "GTD") << "\n";
    std::cout << "Order Type: " << (ordertype == OrderType::BID ? "BID" : "ASK") << "\n";
    std::cout << "Instrument ID: " << idinstrument << "\n";
    std::cout << "Original Quantity: " << originalqty << "\n";
    std::cout << "Firm ID: " << idfirm << "\n";
    std::cout << "================================ \n";
}
