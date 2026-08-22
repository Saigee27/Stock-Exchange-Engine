#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <chrono>
enum class Orderside
{
    BUY,
    SELL
};
class Order
{
    public:
    std::string ticker;
    Orderside side;
    double price;
    int quantity;
    int sequence;
    std::chrono::system_clock::time_point timestamp;
    bool isValid()
    {
        return !ticker.empty() && price > 0 && quantity > 0;
    }
};
#endif