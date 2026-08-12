#ifndef COMPANY_H
#define COMPANY_H
#include <iostream>

class Company
{
    public:
    std::string ticker;
    std::string name;
    std::string sector;

    double price;
    double open;
    double high;
    double low;
    int volume;
};
#endif