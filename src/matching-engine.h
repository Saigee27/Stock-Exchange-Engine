#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include "orderbook.h"
#include "order.h"
#include "trade.h"
#include <algorithm>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>


enum class OrderStatus
    {
        ACCEPTED,
        REJECTED_INVALID
    };

    struct OrderResult
    {
        OrderStatus status;
        OrderId orderId = 0;
    };



class MatchingEngine
{
    private:
    OrderBook& book;
    std::vector<Trade> tradeHistory;
    OrderId nextOrderId = 1;


    public:
    MatchingEngine(OrderBook& book) : book(book) {}

    double getBestBid(const std::string& ticker) const
    {
        return book.getBestBid(ticker);
    }

    double getBestAsk(const std::string& ticker) const
    {
        return book.getBestAsk(ticker);
    }

    double getSpread(const std::string& ticker) const
    {
        return book.getSpread(ticker);
    }

    bool cancelOrder(OrderId id)
    {
        return book.cancelOrder(id);
    }
    

    OrderResult processOrder(Order order)
    {
        if (!order.isValid())
        {
            return {OrderStatus::REJECTED_INVALID,0};
        }

        order.id=nextOrderId++;

        if(order.side == Orderside::BUY)
        {
            book.addBuyOrders(order);
        }
        if(order.side == Orderside::SELL)
        {
            book.addSellOrders(order);
        }
        matchOrders(order.ticker);

        return {OrderStatus::ACCEPTED,order.id};
    }

    bool canMatch(const std::string& ticker)
        {
           std::vector<Order>& buy = book.buyOrders(ticker);
           std::vector<Order>& sell = book.sellOrders(ticker);

           if(buy.empty() || sell.empty())
           {
            return false;
           }

           return buy.front().price >= sell.front().price;
        }

    Trade ExecuteTrade(const std::string& ticker)
    {
        std::vector<Order>& buys = book.buyOrders(ticker);
        std::vector<Order>& sells = book.sellOrders(ticker);

        Order& buy = buys.front();
        Order& sell = sells.front();

        Trade trade;

        trade.ticker = ticker;
        trade.buyOrderId = buy.id;
        trade.sellOrderId = sell.id;

        trade.price = (buy.sequence < sell.sequence) ? buy.price : sell.price;
        trade.quantity = std::min(buy.quantity, sell.quantity);
        trade.timestamp = std::chrono::system_clock::now();

        buy.quantity -= trade.quantity;
        sell.quantity -= trade.quantity;

        return trade;
    }

    void removeFilledOrders(const std::string& ticker)
    {
        std::vector<Order>& buy = book.buyOrders(ticker);
        std::vector<Order>& sell = book.sellOrders(ticker);

        if(!buy.empty() && buy.front().quantity==0)
        {
            buy.erase(buy.begin());
        }

        if(!sell.empty() && sell.front().quantity==0)
        {
            sell.erase(sell.begin());
        }
    }

    void matchOrders(const std::string& ticker)
    {
        while(canMatch(ticker))
        {
            Trade trade = ExecuteTrade(ticker);
            tradeHistory.push_back(trade);
            removeFilledOrders(ticker);
        }
    }

    const std::vector<Trade>& trades() const
{
    return tradeHistory;
}

    double getLastTradedPrice(const std::string& ticker) const
    {
        for (auto it = tradeHistory.rbegin();
                it != tradeHistory.rend();
                    ++it)
        {
            if(it->ticker==ticker)
            {
                return it->price;
            }
        }

        return 0;
    }

    void showTradeHistory()
    {
        std::cout << "\nTRADE HISTORY\n";
        for(const Trade& trade : tradeHistory)
        {
            std::time_t time = std::chrono::system_clock::to_time_t(trade.timestamp);
            std::tm* localTime = std::localtime(&time);
            std::cout << trade.ticker
                        << " | Rs." << trade.price
                        << " | Qty: " << trade.quantity
                        << " | "
                        << std::put_time(localTime, "%d-%m-%Y %H:%M:%S")
                        << "\n";
        }
    }

};
#endif