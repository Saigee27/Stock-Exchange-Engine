#ifndef ORDER_H
#define ORDER_H
#include <iostream>
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
    bool isValid()
    {
        return !ticker.empty() && price > 0 && quantity > 0;
    }
};
#endif