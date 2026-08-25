#ifndef EXCHANGE_H
#define EXCHANGE_H
#include "matching-engine.h"
#include "order.h"
class Exchange
{
    private:
    MatchingEngine& engine;
    public:
    Exchange(MatchingEngine& engine) : engine(engine)
    {
    }
    void submitOrder(Order Order);
};
#endif