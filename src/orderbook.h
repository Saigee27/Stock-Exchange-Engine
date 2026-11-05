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

    int bidCount (const std::string& ticker) const
    {
        int count = 0;

        for(const Order& order : BuyOrders)
        {
            if(order.ticker == ticker)
            {
                count++;
            }
        }
        return count;
    }

    int askCount(const std::string& ticker) const
    {
        int count = 0;
        
        for(const Order& order : SellOrders)
        {
            if(order.ticker == ticker)
            {
                count++;
            }
        }
        return count;
    }


    bool cancelOrder(OrderId id)
    {
        auto buy = std::find_if(BuyOrders.begin(), BuyOrders.end(), [id](const Order& order)
    {
        return order.id == id;
    });

    if (buy != BuyOrders.end())
    {
        BuyOrders.erase(buy);
        return true;
    }

    auto sell = std::find_if(SellOrders.begin(), SellOrders.end(), [id](const Order& order)
    {
        return order.id == id;
    });

    if(sell != SellOrders.end())
    {
        SellOrders.erase(sell);
        return true;
    }

    return false;

    }
};
#endif