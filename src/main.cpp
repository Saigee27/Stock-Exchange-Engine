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
    Order buy1;
    buy1.ticker = "APEX";
    buy1.side = Orderside::BUY;
    buy1.price = 350.50;
    buy1.quantity = 10;

    Order buy2;
    buy2.ticker = "APEX";
    buy2.side = Orderside::BUY;
    buy2.price = 352.50;
    buy2.quantity = 20;

    Order buy3;
    buy3.ticker = "APEX";
    buy3.side = Orderside::BUY;
    buy3.price = 351.00;
    buy3.quantity = 15;

    Order sell1;
    sell1.ticker = "APEX";
    sell1.side = Orderside::SELL;
    sell1.price = 355.00;
    sell1.quantity = 10;

    Order sell2;
    sell2.ticker = "APEX";
    sell2.side = Orderside::SELL;
    sell2.price = 353.50;
    sell2.quantity = 5;

    Order sell3;
    sell3.ticker = "APEX";
    sell3.side = Orderside::SELL;
    sell3.price = 357.00;
    sell3.quantity = 20;

    book.addBuyOrders(buy1);
    book.addBuyOrders(buy2);
    book.addBuyOrders(buy3);

    book.addSellOrders(sell1);
    book.addSellOrders(sell2);
    book.addSellOrders(sell3);

    std::cout << "\nORDER BOOK TEST\n";

    std::cout << "\nBUY ORDERS\n";
    for (const Order& order : book.BuyOrders)
    {
        std::cout << "APEX | Rs" << order.price
                << " | " << order.quantity
                << " | Seq " << order.sequence << "\n";
    }

    std::cout << "\nSELL ORDERS\n";
    for (const Order& order : book.SellOrders)
    {
        std::cout << "APEX | Rs" << order.price
                << " | " << order.quantity
                << " | Seq " << order.sequence << "\n";
    }

    std::cout << "\nBest Bid: Rs" << book.getBestBid() << "\n";
    std::cout << "Best Ask: Rs" << book.getBestAsk() << "\n";
    std::cout << "Spread: Rs" << book.getSpread() << "\n";

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