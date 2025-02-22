#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H

#include <thread>
#include <atomic>
#include <chrono>
#include "OrderBook.hpp"
#include "InstrumentManager.hpp"

class MatchingEngine {
private:
    OrderBook& orderBook;
    InstrumentManager& instrumentManager;
    std::thread engineThread;
    std::atomic<bool> isRunning;
    
    void run();  // Méthode exécutée dans le thread
    void checkGTDOrders();  // Vérification des ordres GTD

public:
    MatchingEngine(OrderBook& ob, InstrumentManager& im);
    ~MatchingEngine();
    
    void start();  // Démarrer le moteur
    void stop();   // Arrêter le moteur
    bool isEngineRunning() const;
    void displayEngineStatus() const;

    // Méthodes d'ajout d'ordres (thread-safe)
    bool addAndValidateOrder(const Order& order);
};

#endif //MATCHINGENGINE_H