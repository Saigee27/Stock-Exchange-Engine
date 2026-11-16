#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <iostream>
#include <vector>
#include "order.h"
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <string>

struct TickerBook
{
    std::vector<Order> BuyOrders;
    std::vector<Order> SellOrders;

    int nextSequence = 1;
};

class OrderBook
{
    private:
    std::unordered_map<std::string, TickerBook> books;

    public:
    std::vector<Order>& buyOrders(const std::string& tickers)
    {
        return books[tickers].BuyOrders;
    }

    std::vector<Order>& sellOrders(const std::string& tickers)
    {
        return books[tickers].SellOrders;
    }

    void addBuyOrders(Order order)
    {
        TickerBook& currentbook = books[order.ticker];
        order.sequence = currentbook.nextSequence++;
        order.timestamp = std::chrono::system_clock::now();

        currentbook.BuyOrders.push_back(order);

        std::sort(currentbook.BuyOrders.begin(), currentbook.BuyOrders.end(), [](const Order& a, const Order& b)
    {
        if(a.price != b.price)
        {
            return a.price > b.price;
        }

        return a.sequence < b.sequence;
    });
    }


    void addSellOrders(Order order)
    {
        TickerBook& currentbook = books[order.ticker];
        order.sequence = currentbook.nextSequence++;
        order.timestamp = std::chrono::system_clock::now();

        currentbook.SellOrders.push_back(order);

        std::sort(currentbook.SellOrders.begin(), currentbook.SellOrders.end(), [](const Order& a, const Order& b)
    {
        if(a.price != b.price)
        {
            return a.price < b.price;
        }

        return a.sequence < b.sequence;
    });
    }


    double getBestBid(const std::string& ticker) const
    {
        auto it = books.find(ticker);

        if(it==books.end() || it->second.BuyOrders.empty())
        {
            return 0;
        }

        return it->second.BuyOrders.front().price;
    }

    double getBestAsk(const std::string& ticker) const
    {
        auto it = books.find(ticker);
        if(it==books.end() || it->second.SellOrders.empty())
        {
            return 0;
        }

        return it->second.SellOrders.front().price;
    }

    double getSpread(const std::string& ticker) const
    {
        double bestBid = getBestBid(ticker);
        double bestAsk = getBestAsk(ticker);

        if(bestAsk==0 || bestBid==0)
        {
            return 0;
        }

        return bestAsk - bestBid;
    }

    int bidcount(const std::string& ticker) const
    {
        auto it = books.find(ticker);

        if(it==books.end())
        {
            return 0;
        }

        return static_cast<int>(it->second.BuyOrders.size());
    }

    int askcount(const std::string& ticker) const
    {
        auto it = books.find(ticker);

        if(it==books.end())
        {
            return 0;
        }

        return static_cast<int> (it->second.SellOrders.size());
    }

    int totalBidCount() const
    {
        int count = 0;

        for(const auto& entry : books)
        {
            count+=static_cast<int>(entry.second.BuyOrders.size());
        }

        return count;
    }

    int totalAskCount() const
    {
        int count = 0;

        for(const auto& entry : books)
        {
            count+=static_cast<int> (entry.second.SellOrders.size());
        }
        return count;
    }

    bool cancelOrder(OrderId id)
    {
        for(auto& entry : books)
        {
            auto& buys = entry.second.BuyOrders;

            auto buy = std::find_if(buys.begin(), buys.end(), [id](const Order& order)
        {
            return order.id == id;
        });

        if(buy != buys.end())
        {
            buys.erase(buy);
            return true;
        }

            auto& sells = entry.second.SellOrders;
            auto sell = std::find_if(sells.begin(), sells.end(), [id](const Order& order)
        {
            return order.id==id;
        });

        if(sell != sells.end())
        {
            sells.erase(sell);
            return true;
        }
        }
        return false;
    }
    
};

#endif