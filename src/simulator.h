#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <vector>
#include <random>
#include <string>
#include "order.h"

class Simulator
{
    private:
    std::mt19937 rng;
    std::vector <std::string> tickers;
    public:
    Simulator(const std::vector<std::string>& tickers, unsigned int seed);
    Order generateOrder();
};

#endif