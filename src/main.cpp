#include <iostream>
#include <cstdlib>
#include <ctime>
#include "market.h"
#include "order.h"
#include "orderbook.h"
#include "matching-engine.h"
int main()
{
    srand(time(0));
    Market market;
    Order order;
    market.initialize();
    OrderBook book;
    MatchingEngine engine(book); 


    Order buy;
    buy.ticker = "NVID";
    buy.side = Orderside::BUY;
    buy.price = 360.00;
    buy.quantity = 30;

    Order sell1;
    sell1.ticker = "APPL";
    sell1.side = Orderside::SELL;
    sell1.price = 353.00;
    sell1.quantity = 10;

    Order sell2;
    sell2.ticker = "NVID";
    sell2.side = Orderside::SELL;
    sell2.price = 355.00;
    sell2.quantity = 15;

    Order sell3;
    sell3.ticker = "GGL";
    sell3.side = Orderside::SELL;
    sell3.price = 358.00;
    sell3.quantity = 20;

    book.addBuyOrders(buy);
    book.addSellOrders(sell1);
    book.addSellOrders(sell2);
    book.addSellOrders(sell3);

    engine.matchOrders();

    engine.showTradeHistory();


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