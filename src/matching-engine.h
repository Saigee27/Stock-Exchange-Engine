#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include "orderbook.h"
#include "order.h"
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

};
#endif