#include "../src/matching-engine.h"
#include <iostream>
using namespace std;
#include <string>

int passed = 0;
int failed = 0;

void check(bool condition, const std::string& name)
{
    if (condition)
    {
        cout << "[PASS] " << name << '\n';
        passed++;
    }

    else
    {
        std::cout << "[FAIL] " << name << '\n';
        failed++;
    }
}


Order makeOrder(std::string ticker, Orderside side, double price, int quantity)
{
    Order order;
    order.ticker = ticker;
    order.quantity = quantity;
    order.side = side;
    order.price = price;
    return order;
}

int main()
{
    // TEST 1: Partial fill
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 110, 10));
        engine.processOrder(makeOrder("TATA", Orderside::SELL, 100, 4));

        check(book.BuyOrders.size() == 1 &&
              book.BuyOrders[0].quantity == 6 &&
              book.SellOrders.empty(),
              "Partial fill: BUY 10, SELL 4");
    }

    // TEST 2: Fully filled orders
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 110, 5));
        engine.processOrder(makeOrder("TATA", Orderside::SELL, 100, 5));

        check(book.BuyOrders.empty() && book.SellOrders.empty(),
              "Both orders fully filled");
    }

    // TEST 3: Different tickers must not match
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 120, 10));
        engine.processOrder(makeOrder("RELIANCE", Orderside::SELL, 100, 10));

        check(book.BuyOrders.size() == 1 &&
              book.SellOrders.size() == 1,
              "Different tickers do not match");
    }

    // TEST 4: Non-crossing prices
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 100, 10));
        engine.processOrder(makeOrder("TATA", Orderside::SELL, 105, 10));

        check(book.BuyOrders.size() == 1 &&
              book.SellOrders.size() == 1,
              "Non-crossing prices do not match");
    }

    // TEST 5: Invalid order rejected
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 100, -5));

        check(book.BuyOrders.empty(),
              "Negative quantity rejected");
    }

    std::cout << "\n========== TEST SUMMARY ==========\n";
    std::cout << "Passed: " << passed << '\n';
    std::cout << "Failed: " << failed << '\n';

    return failed == 0 ? 0 : 1;


}