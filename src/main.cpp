#include <iostream>
#include <cstdlib>
#include <ctime>
#include "market.h"
#include "order.h"
#include "orderbook.h"
int main()
{
    srand(time(0));
    Market market;
    Order order;
    market.initialize();
    OrderBook book;
    Order buy4;
    buy4.ticker = "APEX";
    buy4.side = Orderside::BUY;
    buy4.price = 350;
    buy4.quantity = 50;

    Order buy5;
    buy5.ticker = "APEX";
    buy5.side = Orderside::BUY;
    buy5.price = 350;
    buy5.quantity = 25;

    book.addBuyOrders(buy4);
    book.addBuyOrders(buy5);

for (const Order& order : book.BuyOrders)
{
    std::cout << "APEX | Rs"
              << order.price
              << " | "
              << order.quantity
              << " | Seq "
              << order.sequence
              << "\n";
}

    std::cout << "\n";
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