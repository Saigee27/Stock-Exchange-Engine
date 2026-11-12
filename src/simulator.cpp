#include "simulator.h"

Simulator::Simulator(const std::vector <std::string>& tickers, unsigned int seed) : rng(seed), tickers(tickers)
{
}

Order Simulator::generateOrder()
{
    Order order;

    if(tickers.empty())
    {
        return order;
    }

    std::uniform_int_distribution<int> tickerdist(0, static_cast<int>(tickers.size())-1);

    std::uniform_int_distribution<int> sidedist(0,1);
    std::uniform_int_distribution<int> pricedist(100,500);
    std::uniform_int_distribution<int> quantitydist(1,100);

    order.ticker = tickers[tickerdist(rng)];

    order.price = pricedist(rng);
    order.quantity = quantitydist(rng);

    order.side = (sidedist(rng)==0) ? Orderside::BUY : Orderside::SELL;

    return order;
}