#include <iostream>
#include <cstdlib>
#include <ctime>
#include "market.h"
#include "order.h"
int main()
{
    srand(time(0));
    Market market;
    Order order;
    order.ticker = "APEX";
    order.side = Orderside::BUY;
    order.price = 350.50;
    order.quantity = 10;
    market.initialize();
    std::cout << "\n";
    std::cout << "ORDER TEST\n";
    std::cout << "Ticker: " << order.ticker << "\n";
    std::cout << "Price: Rs." << order.price << "\n";
    std::cout << "Quantity: " << order.quantity << "\n";
    std::cout << "============================================\n";
    std::cout << "        SEE | STOCK EXCHANGE ENGINE         \n";
    std::cout << "============================================\n";

    std::cout << "\n";
    std::cout << "MARKET STATUS: OPEN\n";
    std::cout << "Cash: Rs. 15,000.00\n";

    std::cout << "\n";
    std::cout << "--------------- MARKET WATCH ---------------\n";
    std::cout << "Ticker    Price      Open       High       Low     Volume\n";
    std::cout << "----------------------------------------------------------\n";

    for (int i=0; i<market.companycount; i++)
    {
        std::cout << market.company[i].ticker << "      "
          << "Rs."<< market.company[i].price << "     "
          << "Rs." << market.company[i].open << "     "
          << "Rs." << market.company[i].high << "     "
          << "Rs." << market.company[i].low << "   "
          <<  market.company[i].volume << "\n";
    }

    std::cout << "\n";
    std::cout << "--------------- MENU -----------------------\n";
    std::cout << "[1] Buy\n";
    std::cout << "[2] Sell\n";
    std::cout << "[3] Portfolio\n";
    std::cout << "[4] Market\n";
    std::cout << "[5] Exit\n";

    return 0;
}