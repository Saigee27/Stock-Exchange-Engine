#include "exchange.h"
#include "matching-engine.h"

OrderResult Exchange::submitOrder(Order order)
{
    engine.processOrder(order);
}