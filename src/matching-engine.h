#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include "orderbook.h"
#include "order.h"
#include "trade.h"
#include <algorithm>
class MatchingEngine
{
    private:
    OrderBook& book;
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

};
#endif