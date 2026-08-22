#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <iostream>
#include <vector>
#include "order.h"
#include <algorithm>
class OrderBook
{
    public:
    std::vector<Order>BuyOrders;
    std::vector<Order>SellOrders;
    int nextsequence = 1;

    void addBuyOrders(Order order)
    {
        order.sequence = nextsequence++;
        order.timestamp = std::chrono::system_clock::now();
        BuyOrders.push_back(order);

        std::sort (BuyOrders.begin(), BuyOrders.end(), [] (const Order& a, const Order& b)
        {
            if(a.price != b.price)
            {
                return a.price > b.price;
            }

            return a.sequence < b.sequence;
        });
    }

    void addSellOrders(Order order)
    {
        order.sequence = nextsequence++;
        order.timestamp = std::chrono::system_clock::now();
        SellOrders.push_back(order);

        std::sort (SellOrders.begin(), SellOrders.end(), [] (const Order& a, const Order& b)
    {
        if(a.price != b.price)
        {
            return a.price < b.price;
        }

        return a.sequence < b.sequence;
    });
    }

    double getBestBid()
    {
        if(BuyOrders.empty())
        {
            return 0;
        }
        return BuyOrders[0].price;
    }

    double getBestAsk()
    {
        if(SellOrders.empty())
        {
            return 0;
        }
        return SellOrders[0].price;
    }

    double getSpread()
    {
        if(BuyOrders.empty() || SellOrders.empty())
        {
            return 0;
        }
        return getBestAsk() - getBestBid();
    }
};
#endif