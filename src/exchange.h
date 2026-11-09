#ifndef EXCHANGE_H
#define EXCHANGE_H
#include "matching-engine.h"
#include "order.h"
class Exchange
{
    private:
    MatchingEngine& engine;
    public:
    bool cancelOrder(OrderId id);
    Exchange(MatchingEngine& engine) : engine(engine)
    {
    }
    OrderResult submitOrder(Order Order);

    double getBestBid(const std::string& ticker) const;
    double getBestAsk(const std::string& ticker) const;
    double getSpread(const std::string& ticker) const;
    double getLastTradedPrice(const std::string& ticker) const;
};
#endif