#include "OrderBook.hpp"

// Trade display method
void Trade::display() const
{
    std::time_t trade_time = std::chrono::system_clock::to_time_t(timestamp);
    std::cout << "====== Trade Information =======\n";
    std::cout << "Trade ID: " << tradeId << "\n";
    std::cout << "Buy Order ID: " << buyOrderId << "\n";
    std::cout << "Sell Order ID: " << sellOrderId << "\n";
    std::cout << "Market Identification Code (MIC): " << marketIdentificationCode << "\n";
    std::cout << "Trading Currency: " << tradingCurrency << "\n";
    std::cout << "Price: " << price << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Timestamp: " << std::ctime(&trade_time);
    std::cout << "================================\n";
}

// Constructor
OrderBook::OrderBook() : nextTradeId(1)
{
}

void OrderBook::addOrder(const Order& order)
{
    // Insert BID orders into bidOrders map
    if (order.ordertype == OrderType::BID)
    {
        bidOrders[order.price].push_back(order);
    }
    // Insert ASK orders into askOrders map
    else if (order.ordertype == OrderType::ASK)
    {
        askOrders[order.price].push_back(order);
    }

    // Try to match orders after adding a new order
    int matches = matchOrders();
    if (matches > 0)
    {
        std::cout << "Added order resulted in " << matches << " trade(s)" << std::endl;
    }
}

void OrderBook::cleanupExecutedOrders()
{
    // Nettoyer les BID orders
    for (auto it = bidOrders.begin(); it != bidOrders.end();)
    {
        it->second.erase(
            std::remove_if(it->second.begin(), it->second.end(),
                           [](const Order& o) { return o.quantity == 0; }),
            it->second.end()
        );
        if (it->second.empty())
        {
            it = bidOrders.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Nettoyer les ASK orders
    for (auto it = askOrders.begin(); it != askOrders.end();)
    {
        it->second.erase(
            std::remove_if(it->second.begin(), it->second.end(),
                           [](const Order& o) { return o.quantity == 0; }),
            it->second.end()
        );
        if (it->second.empty())
        {
            it = askOrders.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

int OrderBook::matchOrders()
{
    int tradesExecuted = 0;

    while (!bidOrders.empty() && !askOrders.empty())
    {
        auto highestBidIt = bidOrders.begin();
        auto lowestAskIt = askOrders.begin();

        // Chercher un appariement possible
        bool matchFound = false;
        for (auto& bidOrder : highestBidIt->second)
        {
            for (auto& askOrder : lowestAskIt->second)
            {
                // Vérifier si les ordres sont pour le même instrument
                if (bidOrder.price >= askOrder.price && // Condition de prix
                    bidOrder.idinstrument == askOrder.idinstrument &&
                    bidOrder.marketIdentificationCode == askOrder.marketIdentificationCode &&
                    bidOrder.tradingCurrency == askOrder.tradingCurrency)
                {
                    std::cout << "\nMatching orders found:"
                        << "\nBID: " << bidOrder.idorder << " Price: " << bidOrder.price
                        << "\nASK: " << askOrder.idorder << " Price: " << askOrder.price << std::endl;

                    // Calculer la quantité à échanger
                    int tradeQuantity = std::min(bidOrder.quantity, askOrder.quantity);

                    // Créer une transaction
                    Trade trade;
                    trade.tradeId = nextTradeId++;
                    trade.buyOrderId = bidOrder.idorder;
                    trade.sellOrderId = askOrder.idorder;
                    trade.marketIdentificationCode = bidOrder.marketIdentificationCode;
                    trade.tradingCurrency = bidOrder.tradingCurrency;
                    trade.price = askOrder.price;
                    trade.quantity = tradeQuantity;
                    trade.timestamp = std::chrono::system_clock::now();

                    trades.push_back(trade);

                    // Mettre à jour les quantités
                    bidOrder.quantity -= tradeQuantity;
                    askOrder.quantity -= tradeQuantity;

                    tradesExecuted++;
                    matchFound = true;

                    std::cout << "Executed trade: " << tradeQuantity
                        << " units at price " << trade.price << std::endl;

                    // Si l'un des ordres est complètement exécuté, le retirer
                    if (bidOrder.quantity == 0 || askOrder.quantity == 0)
                    {
                        break;
                    }
                }
            }
            if (matchFound) break;
        }

        // Nettoyer les ordres complètement exécutés
        cleanupExecutedOrders();

        // Si aucun appariement n'a été trouvé, sortir de la boucle
        if (!matchFound) break;
    }

    return tradesExecuted;
}

// Remove an order from the order book
void OrderBook::removeOrder(int idorder, const std::string& marketIdentificationCode,
                            const std::string& tradingCurrency, OrderType orderType)
{
    // Implementation remains the same
    if (orderType == OrderType::BID)
    {
        // Search and remove from bid orders
        for (auto it = bidOrders.begin(); it != bidOrders.end(); ++it)
        {
            auto& ordersAtPrice = it->second;
            for (auto orderIt = ordersAtPrice.begin(); orderIt != ordersAtPrice.end(); ++orderIt)
            {
                if (orderIt->idorder == idorder &&
                    orderIt->marketIdentificationCode == marketIdentificationCode &&
                    orderIt->tradingCurrency == tradingCurrency)
                {
                    ordersAtPrice.erase(orderIt);
                    // Check if price level is now empty
                    if (ordersAtPrice.empty())
                    {
                        bidOrders.erase(it);
                    }
                    return;
                }
            }
        }
    }
    else if (orderType == OrderType::ASK)
    {
        // Search and remove from ask orders
        for (auto it = askOrders.begin(); it != askOrders.end(); ++it)
        {
            auto& ordersAtPrice = it->second;
            for (auto orderIt = ordersAtPrice.begin(); orderIt != ordersAtPrice.end(); ++orderIt)
            {
                if (orderIt->idorder == idorder &&
                    orderIt->marketIdentificationCode == marketIdentificationCode &&
                    orderIt->tradingCurrency == tradingCurrency)
                {
                    ordersAtPrice.erase(orderIt);
                    // Check if price level is now empty
                    if (ordersAtPrice.empty())
                    {
                        askOrders.erase(it);
                    }
                    return;
                }
            }
        }
    }
}

// Display all orders in the order book
void OrderBook::displayOrderBook() const
{
    std::cout << "\n\n============== ORDER BOOK ==============\n";

    std::cout << "\n\nBID Orders=====================\n";
    for (const auto& bid : bidOrders)
    {
        std::cout << "Price LEVEL: " << bid.first << "\n";
        for (const auto& order : bid.second)
        {
            order.display();
        }
    }

    std::cout << "\n\nASK Orders=====================\n";
    for (const auto& ask : askOrders)
    {
        std::cout << "Price LEVEL: " << ask.first << "\n";
        for (const auto& order : ask.second)
        {
            order.display();
        }
    }

    std::cout << "\n\n============== END OF ORDER BOOK ==============\n";
}

// Display a specific order
void OrderBook::displayOrder(int idorder, const std::string& marketIdentificationCode,
                             const std::string& tradingCurrency) const
{
    // Implementation remains the same
    // Search first in BID
    for (const auto& bid : bidOrders)
    {
        for (const auto& order : bid.second)
        {
            if (order.idorder == idorder &&
                order.marketIdentificationCode == marketIdentificationCode &&
                order.tradingCurrency == tradingCurrency)
            {
                order.display(); // Affiche l'ordre trouvé
                return; // Si trouvé, on quitte la fonction
            }
        }
    }

    // Search secondly in ASK if not in BID
    for (const auto& ask : askOrders)
    {
        for (const auto& order : ask.second)
        {
            if (order.idorder == idorder &&
                order.marketIdentificationCode == marketIdentificationCode &&
                order.tradingCurrency == tradingCurrency)
            {
                order.display(); // Affiche l'ordre trouvé
                return; // Si trouvé, on quitte la fonction
            }
        }
    }

    std::cout << "Order not found in the orderbook.\n"; // Message si l'ordre n'est pas trouvé dans l'OrderBook
}

// Display all trades that have occurred
void OrderBook::displayTrades() const
{
    std::cout << "\n\n============== TRADE HISTORY ==============\n";

    if (trades.empty())
    {
        std::cout << "No trades have been executed yet.\n";
    }
    else
    {
        for (const auto& trade : trades)
        {
            trade.display();
        }
    }

    std::cout << "\n\n============== END OF TRADE HISTORY ==============\n";
}
