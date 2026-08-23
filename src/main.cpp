#include <iostream>
#include <cstdlib>
#include <ctime>
#include "market.h"
#include "order.h"
#include "orderbook.h"
#include "trader.h"
#include "matching-engine.h"
int main()
{
    srand(time(0));
    Market market;
    Order order;
    market.initialize();
    OrderBook book;
    MatchingEngine engine(book); 
    
    Trader trader1(1, "Trader_01", market);

for(int i = 0; i < 10; i++)
{
    Order order = trader1.generateOrder();

    std::cout << trader1.NAME << " | "
              << order.ticker << " | ";

    if(order.side == Orderside::BUY)
    {
        std::cout << "BUY";
    }
    else
    {
        std::cout << "SELL";
    }

    std::cout << " | Rs." << order.price
              << " | Qty: " << order.quantity
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