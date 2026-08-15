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

    void addBuyOrders(Order order)
    {
        BuyOrders.push_back(order);

        std::sort (BuyOrders.begin(), BuyOrders.end(), [] (const Order& a, const Order& b)
        {
            return a.price > b.price;
        });
    }

    void addSellOrders(Order order)
    {
        SellOrders.push_back(order);

        std::sort (SellOrders.begin(), SellOrders.end(), [] (const Order& a, const Order& b)
    {
        return a.price < b.price;
    });
    }
};
#endif