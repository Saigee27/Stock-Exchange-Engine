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