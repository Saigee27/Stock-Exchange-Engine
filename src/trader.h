#ifndef TRADER_H
#define TRADER_H
#include <iostream>
#include "order.h"
#include "market.h"
class Trader
{
    public:
    int ID;
    std::string NAME;
    Trader(int id, std::string name, Market& market) : ID(id), NAME(name), MARKET(market)
    {

    }
    Order generateOrder();

    private:
    Market& MARKET;
};
#endif