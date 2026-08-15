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
};
#endif