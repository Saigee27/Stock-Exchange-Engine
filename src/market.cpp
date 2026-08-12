#include "market.h"
#include <cstdlib>

void Market::initialize()
{
   std::string tickers[10] = {
        "APEX", "NOVA", "VRTX", "QSYS",
        "TENG", "OMNI", "LUMO", "CYBR",
        "AURA", "NEXA"
    };

    std::string names[10] = {
        "Apex Technologies",
        "Nova Finance",
        "Vertex Motors",
        "Quantum Systems",
        "Titan Energy",
        "Omni Industries",
        "Lumo Healthcare",
        "Cyber Dynamics",
        "Aura Consumer",
        "Nexa Telecom"
    };

    std::string sectors[10] = {
         "Technology",
        "Financials",
        "Automotive",
        "Technology",
        "Energy",
        "Industrials",
        "Healthcare",
        "Technology",
        "Consumer",
        "Telecom"
    };

    for (int i=0; i<10; i++)
    {
        company[i].ticker = tickers[i];
        company[i].name = names[i];
        company[i].sector = sectors[i];

        company[i].price = rand() % 401 + 100;
        company[i].open = company[i].price;
        company[i].high = company[i].price;
        company[i].low = company[i].price;

        company[i].volume = 0;
        companycount++;
    }
}