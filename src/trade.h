#ifndef TRADE_H
#define TRADE_H
#include <iostream>
#include <chrono>
class Trade
{
    public:
    std::string ticker;
    int quantity;
    double price;
    std::chrono::system_clock::time_point timestamp;
};
#endif