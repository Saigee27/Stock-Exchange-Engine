#include "exchange.h"
#include "matching-engine.h"

void Exchange::submitOrder(Order order)
{
    engine.processOrder(order);
}