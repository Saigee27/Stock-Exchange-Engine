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
    int matchedBuyIndex = -1;
    int matchedSellIndex = -1;
    OrderId nextOrderId = 1;
    public:
    MatchingEngine(OrderBook& book) : book(book)
    {
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
        matchOrders();

        return {OrderStatus::ACCEPTED,order.id};
    }

    bool canMatch()
        {
            matchedBuyIndex = -1;
            matchedSellIndex = -1;
        if(book.BuyOrders.empty() || book.SellOrders.empty())
        {
            return false;
        }
        for(int i=0; i < book.BuyOrders.size(); i++)
        {
            for(int j=0; j < book.SellOrders.size(); j++)
            {
                if(book.BuyOrders[i].ticker==book.SellOrders[j].ticker)
                {
                    if(book.BuyOrders[i].price>=book.SellOrders[j].price)
                    {
                        matchedBuyIndex=i;
                        matchedSellIndex=j;
                        return true;
                    }
                }
            }
        }
        return false;
        }

    Trade ExecuteTrade()
    {
        Order& buy = book.BuyOrders[matchedBuyIndex];
        Order& sell = book.SellOrders[matchedSellIndex];
        Trade trade;
        trade.ticker = buy.ticker;
        trade.buyOrderId = buy.id;
        trade.sellOrderId = sell.id;
        trade.price = (buy.sequence < sell.sequence) ? buy.price : sell.price;
        trade.quantity = std::min(buy.quantity, sell.quantity);
        trade.timestamp = std::chrono::system_clock::now();
        buy.quantity -= trade.quantity;
        sell.quantity -= trade.quantity;
        return trade;
    }

    void removeFilledOrders()
    {
        if(matchedBuyIndex >= 0 && matchedBuyIndex < book.BuyOrders.size() && book.BuyOrders[matchedBuyIndex].quantity == 0)
        {
            book.BuyOrders.erase(book.BuyOrders.begin() + matchedBuyIndex);
        }
        if(matchedSellIndex >= 0 && matchedSellIndex < book.SellOrders.size() && book.SellOrders[matchedSellIndex].quantity == 0)
        {
            book.SellOrders.erase(book.SellOrders.begin() + matchedSellIndex);
        }
    }

    void matchOrders()
    {
        while(canMatch())
        {
            Trade trade = ExecuteTrade();
            tradeHistory.push_back(trade);
            removeFilledOrders();
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