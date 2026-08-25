#ifndef TRADER_H
#define TRADER_H
#include <iostream>
#include "order.h"
#include "market.h"
class Trader
{
    public:
    int ID;
    Trader(int id, Market& market) : ID(id), MARKET(market)
    {

    }
    Order generateOrder();

    private:
    Market& MARKET;
};
#endif