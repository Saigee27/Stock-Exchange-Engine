#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "market.h"
#include "order.h"
#include "orderbook.h"
#include "trader.h"
#include "matching-engine.h"
#include "exchange.h"
int main()
{
    srand(time(0));
    Market market;
    Order order;
    market.initialize();
    OrderBook book;
    MatchingEngine engine(book);
    Exchange exchange(engine);
    std::vector <Trader> traders;
    int numberOfTraders=10;
    const int marketRounds=10;
    for (int i=1; i<=numberOfTraders; i++)
    {
        traders.emplace_back(i, market);
    } 

    for(int i=1; i<=marketRounds; i++)
    {
         std::cout << "\n========== MARKET ROUND "
              << i
              << " ==========\n";

        for (Trader& trader : traders)
        {
            order = trader.generateOrder();

            std::cout << "\n";
            std::cout << "Ticker: " << order.ticker
                    << " | Side: "
                    << (order.side == Orderside::BUY ? "BUY" : "SELL")
                    << " | Price: Rs." << order.price
                    << " | Quantity: " << order.quantity
                    << "\n";

            exchange.submitOrder(order);

            std::cout << "\nBUY ORDERS: "
                    << book.BuyOrders.size() << "\n";

            std::cout << "SELL ORDERS: "
                    << book.SellOrders.size() << "\n";


            
        }

        
    }
    engine.showTradeHistory();

    


std::cout<<"\n";
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