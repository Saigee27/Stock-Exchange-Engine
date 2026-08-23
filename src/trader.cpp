#include "trader.h"
#include <iostream>
#include <cstdlib>
Order Trader::generateOrder()
{
    Order order;
    int index = rand()%MARKET.companycount;
    order.ticker = MARKET.company[index].ticker;

    if(rand()%2==0)
    {
        order.side = Orderside::BUY;
    }
    else
    {
        order.side = Orderside::SELL;
    }

    order.price = MARKET.company[index].price;
    order.quantity = 1 + rand()%20;

    return order;
}