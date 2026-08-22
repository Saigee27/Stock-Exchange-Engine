#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include "orderbook.h"
#include "order.h"
#include "trade.h"
#include <algorithm>
#include <vector>
class MatchingEngine
{
    private:
    OrderBook& book;
    std::vector<Trade> tradeHistory;
    public:
    MatchingEngine(OrderBook& book) : book(book)
    {
    }

    bool canMatch()
        {
        if(book.BuyOrders.empty() || book.SellOrders.empty())
        {
            return false;
        }
        return book.getBestBid() >= book.getBestAsk();
        }

    Trade ExecuteTrade()
    {
        Order& buy = book.BuyOrders[0];
        Order& sell = book.SellOrders[0];
        Trade trade;
        trade.ticker = buy.ticker;
        trade.price = sell.price;
        trade.quantity = std::min(buy.quantity, sell.quantity);
        buy.quantity -= trade.quantity;
        sell.quantity -= trade.quantity;
        return trade;
    }

    void removeFilledOrders()
    {
        if(!book.BuyOrders.empty() && book.BuyOrders[0].quantity == 0)
        {
            book.BuyOrders.erase(book.BuyOrders.begin());
        }
        if(!book.SellOrders.empty() && book.SellOrders[0].quantity == 0)
        {
            book.SellOrders.erase(book.SellOrders.begin());
        }
    }

    void matchOrders()
    {
        while(canMatch())
        {
            Trade trade = ExecuteTrade();
            tradeHistory.push_back(trade);
            removeFilledOrders();
        }
    }

    void showTradeHistory()
    {
        std::cout << "\nTRADE HISTORY\n";
        for(const Trade& trade : tradeHistory)
        {
            std::cout << trade.ticker
                  << " | Rs." << trade.price
                  << " | Qty: " << trade.quantity
                  << "\n";
        }
    }

};
#endif