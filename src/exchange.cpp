#include "exchange.h"
#include "matching-engine.h"

OrderResult Exchange::submitOrder(Order order)
{
    return engine.processOrder(order);
}

bool Exchange::cancelOrder(OrderId id)
{
    return engine.cancelOrder(id);
}


double Exchange::getBestBid(const std::string& ticker) const
{
    return engine.getBestBid(ticker);
}

double Exchange::getBestAsk(const std::string& ticker) const
{
    return engine.getBestAsk(ticker);
}

double Exchange::getSpread(const std::string& ticker) const
{
    return engine.getSpread(ticker);
}

double Exchange::getLastTradedPrice(const std::string& ticker) const
{
    return engine.getLastTradedPrice(ticker);
}