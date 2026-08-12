#ifndef MARKET_H
#define MARKET_H
#include "company.h"
class Market
{
    public:
    Company company[10];
    int companycount=0;

    void initialize();
};
#endif