#ifndef TRADE_H
#define TRADE_H
#include <iostream>
#include <chrono>
#include "order.h"
class Trade
{
    public:
    OrderId buyOrderId = 0;
    OrderId sellOrderId = 0;
    std::string ticker;
    int quantity;
    double price;
    std::chrono::system_clock::time_point timestamp;
};
#endif