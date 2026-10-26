#ifndef TRADER_H
#define TRADER_H
#include <iostream>
#include "order.h"
#include "market.h"

enum class TraderStrategy
{
    RANDOM,
    MOMENTUM,
    VALUE
};

class Trader
{
    public:
    int ID;
    Trader(int id, Market& market, TraderStrategy strategy) : ID(id), MARKET(market), STRATEGY(strategy)
    {

    }
    Order generateOrder();

    private:
    Market& MARKET;
    TraderStrategy STRATEGY;
};
#endif