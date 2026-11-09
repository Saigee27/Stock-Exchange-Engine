
#include "../src/matching-engine.h"
#include "../src/exchange.h"
#include <iostream>
#include <string>

using namespace std;

int passed = 0;
int failed = 0;

// Helper function to check test results
void check(bool condition, const std::string& name)
{
    if (condition)
    {
        cout << "[PASS] " << name << '\n';
        passed++;
    }
    else
    {
        cout << "[FAIL] " << name << '\n';
        failed++;
    }
}

// Helper function to create orders
Order makeOrder(string ticker, Orderside side, double price, int quantity)
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

        check(book.bidCount("TATA") == 1 &&
              book.askCount("TATA") == 0 &&
              book.BuyOrders[0].quantity == 6,
              "Partial fill: BUY 10, SELL 4");
    }

    // TEST 2: Fully filled orders
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 110, 5));
        engine.processOrder(makeOrder("TATA", Orderside::SELL, 100, 5));

        check(book.bidCount("TATA") == 0 &&
              book.askCount("TATA") == 0,
              "Both orders fully filled");

        check(engine.trades().size() == 1 &&
              engine.trades()[0].buyOrderId != 0 &&
              engine.trades()[0].sellOrderId != 0,
              "Trade records both order IDs");
    }

    // TEST 3: Different tickers must not match
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 120, 10));
        engine.processOrder(makeOrder("RELIANCE", Orderside::SELL, 100, 10));

        check(book.bidCount("TATA") == 1 &&
              book.askCount("RELIANCE") == 1,
              "Different tickers do not match");
    }

    // TEST 4: Non-crossing prices
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 100, 10));
        engine.processOrder(makeOrder("TATA", Orderside::SELL, 105, 10));

        check(book.bidCount("TATA") == 1 &&
              book.askCount("TATA") == 1,
              "Non-crossing prices do not match");
    }

    // TEST 5: Invalid order rejected
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 100, -5));

        check(book.bidCount("TATA") == 0,
              "Negative quantity rejected");
    }

    // TEST 6: Incoming SELL trades at resting BUY price
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::BUY, 110, 5));
        engine.processOrder(makeOrder("TATA", Orderside::SELL, 100, 5));

        check(engine.trades().size() == 1 &&
              engine.trades()[0].price == 110,
              "Trade executes at resting BUY price");
    }

    // TEST 7: Incoming BUY trades at resting SELL price
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::SELL, 100, 5));
        engine.processOrder(makeOrder("TATA", Orderside::BUY, 110, 5));

        check(engine.trades().size() == 1 &&
              engine.trades()[0].price == 100,
              "Trade executes at resting SELL price");
    }

    // TEST 8: Same-price orders follow time priority
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::SELL, 100, 3));
        engine.processOrder(makeOrder("TATA", Orderside::SELL, 100, 5));
        engine.processOrder(makeOrder("TATA", Orderside::BUY, 100, 4));

        check(engine.trades().size() == 2 &&
              engine.trades()[0].sellOrderId == 1 &&
              engine.trades()[0].quantity == 3 &&
              engine.trades()[1].sellOrderId == 2 &&
              engine.trades()[1].quantity == 1,
              "Same-price orders follow time priority");
    }

    // TEST 9: One incoming order sweeps multiple price levels
    {
        OrderBook book;
        MatchingEngine engine(book);

        engine.processOrder(makeOrder("TATA", Orderside::SELL, 100, 3));
        engine.processOrder(makeOrder("TATA", Orderside::SELL, 105, 4));
        engine.processOrder(makeOrder("TATA", Orderside::BUY, 110, 6));

        check(engine.trades().size() == 2 &&
              engine.trades()[0].price == 100 &&
              engine.trades()[0].quantity == 3 &&
              engine.trades()[1].price == 105 &&
              engine.trades()[1].quantity == 3 &&
              book.askCount("TATA") == 1,
              "Incoming BUY matches across multiple price levels");
    }

    // TEST 10: Successful cancellation
    {
        OrderBook book;
        MatchingEngine engine(book);

        OrderResult result = engine.processOrder(
            makeOrder("TATA", Orderside::BUY, 90, 10)
        );

        bool cancelled = engine.cancelOrder(result.orderId);

        check(cancelled && book.bidCount("TATA") == 0,
              "Successfully cancel a resting BUY order");
    }

    // TEST 11: Repeated cancellation
    {
        OrderBook book;
        MatchingEngine engine(book);

        OrderResult result = engine.processOrder(
            makeOrder("TATA", Orderside::BUY, 90, 10)
        );

        engine.cancelOrder(result.orderId);

        check(!engine.cancelOrder(result.orderId),
              "Reject cancellation of an already cancelled order");
    }

    // TEST 12: Unknown order ID
    {
        OrderBook book;
        MatchingEngine engine(book);

        check(!engine.cancelOrder(999),
              "Reject cancellation of an unknown order ID");
    }

    // TEST 13: Already-filled order
    {
        OrderBook book;
        MatchingEngine engine(book);

        OrderResult buy = engine.processOrder(
            makeOrder("TATA", Orderside::BUY, 110, 5)
        );

        engine.processOrder(
            makeOrder("TATA", Orderside::SELL, 100, 5)
        );

        check(!engine.cancelOrder(buy.orderId),
              "Reject cancellation of an already filled order");
    }

    // TEST 14: Best Bid
    {
        OrderBook book;
        MatchingEngine engine(book);
        Exchange exchange(engine);

        Order buy1 = makeOrder("TATA", Orderside::BUY, 100, 10);
        Order buy2 = makeOrder("TATA", Orderside::BUY, 110, 10);

        exchange.submitOrder(buy1);
        exchange.submitOrder(buy2);

        check(exchange.getBestBid("TATA") == 110,
              "Best Bid");
    }

    // TEST 15: Best Ask
    {
        OrderBook book;
        MatchingEngine engine(book);
        Exchange exchange(engine);

        Order sell1 = makeOrder("TATA", Orderside::SELL, 120, 10);
        Order sell2 = makeOrder("TATA", Orderside::SELL, 115, 10);

        exchange.submitOrder(sell1);
        exchange.submitOrder(sell2);

        check(exchange.getBestAsk("TATA") == 115,
              "Best Ask");
    }

    // TEST 16: Spread
    {
        OrderBook book;
        MatchingEngine engine(book);
        Exchange exchange(engine);

        Order buy = makeOrder("TATA", Orderside::BUY, 110, 10);
        Order sell = makeOrder("TATA", Orderside::SELL, 115, 10);

        exchange.submitOrder(buy);
        exchange.submitOrder(sell);

        check(exchange.getSpread("TATA") == 5,
              "Spread");
    }

    // TEST 17: Ticker Isolation
    {
        OrderBook book;
        MatchingEngine engine(book);
        Exchange exchange(engine);

        Order tata = makeOrder("TATA", Orderside::BUY, 110, 10);
        Order reliance = makeOrder("RELIANCE", Orderside::BUY, 250, 10);

        exchange.submitOrder(tata);
        exchange.submitOrder(reliance);

        check(exchange.getBestBid("TATA") == 110 &&
              exchange.getBestBid("RELIANCE") == 250,
              "Ticker Isolation");
    }

    // TEST 18: Last Traded Price
    {
        OrderBook book;
        MatchingEngine engine(book);
        Exchange exchange(engine);

        Order buy1 = makeOrder("TATA", Orderside::BUY, 100, 10);
        Order sell1 = makeOrder("TATA", Orderside::SELL, 100, 10);

        Order buy2 = makeOrder("RELIANCE", Orderside::BUY, 250, 10);
        Order sell2 = makeOrder("RELIANCE", Orderside::SELL, 250, 10);

        Order buy3 = makeOrder("TATA", Orderside::BUY, 105, 10);
        Order sell3 = makeOrder("TATA", Orderside::SELL, 105, 10);

        exchange.submitOrder(buy1);
        exchange.submitOrder(sell1);

        exchange.submitOrder(buy2);
        exchange.submitOrder(sell2);

        exchange.submitOrder(buy3);
        exchange.submitOrder(sell3);

        check(exchange.getLastTradedPrice("TATA") == 105 &&
              exchange.getLastTradedPrice("RELIANCE") == 250 &&
              exchange.getLastTradedPrice("INFY") == 0,
              "Last Traded Price");
    }

    // TEST SUMMARY
    std::cout << "\n========== TEST SUMMARY ==========\n";
    std::cout << "Passed: " << passed << '\n';
    std::cout << "Failed: " << failed << '\n';

    return failed == 0 ? 0 : 1;
}
