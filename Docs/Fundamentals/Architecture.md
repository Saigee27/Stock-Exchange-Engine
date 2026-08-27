# Stock Exchange Engine Architecture

## 1. System Overview

The Stock Exchange Engine simulates the core mechanism of a stock exchange:

```text
Trader
  ↓
Order
  ↓
Order Book
  ↓
Matching Engine
  ↓
Trade
```

The system receives buy and sell orders, stores them in an order book, finds compatible orders, and creates trades when matching conditions are satisfied.

---

## 2. Core Components

### Trader

A trader generates orders for companies listed on the exchange.

```text
Trader → generates Order
```

A trader does not directly execute trades. Orders are submitted to the exchange for matching.

---

### Order

An order represents a request to buy or sell shares.

An order contains information such as:

- Ticker
- Side: BUY / SELL
- Price
- Quantity

Example:

```text
Ticker: OMNI
Side: BUY
Price: ₹206
Quantity: 20
```

---

### Order Book

The order book stores active buy and sell orders.

```text
BUY ORDERS
OMNI  ₹206  × 20
OMNI  ₹204  × 10

SELL ORDERS
OMNI  ₹208  × 15
OMNI  ₹210  × 20
```

The order book is organized around orders belonging to the same ticker.

---

### Matching Engine

The matching engine compares buy and sell orders and determines whether they can trade.

A match requires:

```text
Buy.Ticker == Sell.Ticker
```

and:

```text
Buy.Price >= Sell.Price
```

Therefore, an order for one company must never match an order belonging to another company.

Example:

```text
BUY  OMNI  ₹206
SELL OMNI  ₹205
```

Match:

```text
₹206 >= ₹205
```

But:

```text
BUY  OMNI  ₹206
SELL LUMO  ₹200
```

No match:

```text
OMNI != LUMO
```

Ticker isolation is a fundamental rule of the matching engine.

---

## 3. Matching Process

The basic matching process is:

```text
1. Check whether both BUY and SELL orders exist.
2. Compare BUY and SELL orders.
3. Verify that both orders have the same ticker.
4. Verify that the BUY price is greater than or equal to the SELL price.
5. Create a trade when both conditions are satisfied.
6. Reduce the quantities of the matched orders.
7. Remove an order when its remaining quantity reaches zero.
8. Continue matching while compatible orders exist.
```

---

## 4. Price Priority

For a given ticker, the matching engine should prefer the most favorable available price.

For BUY orders:

```text
Higher BUY price = Higher priority
```

For SELL orders:

```text
Lower SELL price = Higher priority
```

Example:

```text
BUY:
₹210 × 10
₹205 × 20
₹200 × 15
```

The ₹210 BUY order has the highest priority.

For sells:

```text
SELL:
₹195 × 10
₹200 × 20
₹205 × 15
```

The ₹195 SELL order has the highest priority.

---

## 5. Quantity Matching

Orders do not necessarily contain equal quantities.

Example:

```text
BUY  OMNI  ₹206 × 20
SELL OMNI  ₹205 × 8
```

Trade:

```text
Quantity = 8
```

Remaining:

```text
BUY  OMNI  ₹206 × 12
```

The matching engine should continue processing the remaining quantity.

---

## 6. Trade Creation

When compatible orders are found, the engine creates a trade.

A trade represents an executed transaction between a buyer and seller.

Example:

```text
BUY  OMNI  ₹206 × 20
SELL OMNI  ₹205 × 8
```

Result:

```text
TRADE
Ticker: OMNI
Price: ₹205
Quantity: 8
```

The remaining BUY quantity is:

```text
20 - 8 = 12
```

The exact trade-price mechanism can be expanded later as the engine becomes more sophisticated.

---

## 7. Important Design Rule

The matching engine must treat each ticker as an independent market.

Conceptually:

```text
OMNI Order Book
    ↓
OMNI Matching

LUMO Order Book
    ↓
LUMO Matching

Other Tickers
    ↓
Independent Matching
```

Orders from different companies must never interact.

This prevents incorrect matches such as:

```text
BUY OMNI
      ×
SELL LUMO
```

even when their prices are compatible.

---

## 8. Current Architecture

The current project can be viewed as:

```text
                    ┌─────────────┐
                    │   Trader    │
                    └──────┬──────┘
                           │
                           ▼
                    ┌─────────────┐
                    │    Order    │
                    └──────┬──────┘
                           │
                           ▼
                    ┌─────────────┐
                    │ Order Book  │
                    └──────┬──────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Matching Engine  │
                  └────────┬─────────┘
                           │
                           ▼
                    ┌─────────────┐
                    │    Trade    │
                    └─────────────┘
```

The architecture will later be extended with more traders, multiple companies, improved order-book structures, trade history, and more efficient matching algorithms.

---

## 9. Core Principle

The key principle of the matching engine is:

> **Orders are matched by ticker first, then by price compatibility and priority.**

This keeps each company's market logically isolated and provides a foundation for building a more realistic exchange engine.