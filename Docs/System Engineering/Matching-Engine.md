# Matching Engine

## 1. Overview

A **Matching Engine** is the core component of an exchange that determines whether incoming buy and sell orders can be executed against each other.

The Order Book stores and prioritizes active orders. The Matching Engine takes those orders and determines when a trade can occur.

The basic flow is:

```text
Incoming Order
      ↓
Order Validation
      ↓
Order Book
      ↓
Matching Engine
      ↓
Trade
      ↓
Market Data
```

The Matching Engine therefore acts as the bridge between **resting orders** and **executed trades**.

---

## 2. Matching Condition

The engine continuously compares the best orders on both sides of the book.

Let:

* (B) = Best Bid
* (A) = Best Ask

A trade can occur when:

[
B \geq A
]

If:

[
B < A
]

there is no match and the orders remain in the Order Book.

### Example

```text
Best Bid = ₹352
Best Ask = ₹353
```

Since:

[
352 < 353
]

no trade occurs.

If the book becomes:

```text
Best Bid = ₹353
Best Ask = ₹353
```

then:

[
353 \geq 353
]

and the orders can match.

---

## 3. Price-Time Priority

SEE uses **price-time priority**.

### Buy Orders

Higher prices receive priority.

```text
₹355
₹352
₹350
```

### Sell Orders

Lower prices receive priority.

```text
₹353
₹355
₹360
```

If two orders have the same price, the order that arrived earlier receives priority.

```text
BUY ₹350 × 10  → Sequence 1
BUY ₹350 × 20  → Sequence 2
```

The sequence-1 order is matched first.

This can be represented as:

[
\text{Priority} =
\begin{cases}
\text{Better Price} & \text{if prices differ}\
\text{Earlier Arrival} & \text{if prices are equal}
\end{cases}
]

---

## 4. Trade Quantity

When two orders match, the amount traded is limited by the smaller available quantity.

[
Q_{\text{trade}} = \min(Q_{\text{buy}}, Q_{\text{sell}})
]

### Example

```text
BUY  = 20 shares
SELL = 5 shares
```

Therefore:

[
Q_{\text{trade}} = \min(20,5)=5
]

The trade executes for **5 shares**.

The remaining quantities become:

```text
BUY  → 15 shares remaining
SELL → 0 shares remaining
```

---

## 5. Partial Fills

A **partial fill** occurs when an order is only partially executed.

Example:

```text
BUY 20 @ ₹353
SELL 5  @ ₹353
```

The engine executes:

```text
5 shares
```

The BUY order remains in the book with:

```text
15 shares
```

The SELL order is completely filled and can be removed.

Partial fills are important because a single large order can trade against multiple smaller orders.

---

## 6. Multiple Matches

The Matching Engine should continue checking the book after a successful trade.

Example:

```text
BUY 30 @ ₹353

SELL 10 @ ₹353
SELL 15 @ ₹353
SELL 20 @ ₹353
```

The engine performs:

```text
Match 1 → 10 shares
Match 2 → 15 shares
Match 3 → 5 shares
```

The original BUY order is completely filled.

The final SELL order has:

```text
20 - 5 = 15 shares
```

remaining.

Therefore, matching is not necessarily a one-order-to-one-order operation.

---

## 7. Execution Price

For the initial SEE implementation, the execution price will be determined by the **resting order**.

Example:

```text
Existing SELL → 10 @ ₹353
Incoming BUY  → 10 @ ₹355
```

The buyer is willing to pay up to ₹355, while the seller is willing to accept ₹353.

The trade executes at:

[
P_{\text{trade}} = ₹353
]

This keeps the initial implementation simple. More sophisticated execution-price rules can be introduced later.

---

## 8. Trade Generation

When a match occurs, the Matching Engine creates a Trade containing the essential execution information.

Conceptually:

```text
Trade
├── Ticker
├── Price
└── Quantity
```

Example:

```text
Ticker:   APEX
Price:    ₹353
Quantity: 5
```

The Trade represents an **executed transaction**, unlike an Order, which represents an intention to buy or sell.

---

## 9. Order Lifecycle

An order can move through several states:

```text
Created
   ↓
Validated
   ↓
Added to Order Book
   ↓
Matched
   ↓
Partially Filled ─────┐
   ↓                  │
Completely Filled ←───┘
```

An order that cannot currently match remains in the Order Book.

---

## 10. Matching Loop

The conceptual matching algorithm is:

```text
while Best Bid >= Best Ask:

    identify best BUY order
    identify best SELL order

    determine trade quantity

    determine execution price

    create Trade

    reduce BUY quantity
    reduce SELL quantity

    remove completely filled orders

    repeat
```

The loop terminates when either:

1. There are no orders on one side of the book, or
2. The Best Bid is lower than the Best Ask.

---

## 11. Order Book vs Matching Engine

These components have different responsibilities.

| Component       | Responsibility                                   |
| --------------- | ------------------------------------------------ |
| Order           | Represents a trader's instruction                |
| Validation      | Determines whether an order is valid             |
| Order Book      | Stores and prioritizes active orders             |
| Matching Engine | Determines whether orders can trade              |
| Trade           | Represents an executed transaction               |
| Market Data     | Updates price, volume, OHLC and other statistics |

The distinction is important:

> **The Order Book organizes potential trades. The Matching Engine creates actual trades.**

---

## 12. SEE Architecture

The current architecture is:

```text
                 SEE
                  │
                  ▼
               Order
                  │
                  ▼
             Validation
                  │
                  ▼
             Order Book
             /         \
        BUY SIDE      SELL SIDE
             \         /
                  ▼
          Matching Engine
                  │
                  ▼
                Trade
                  │
          ┌───────┼────────┐
          ▼       ▼        ▼
       Volume   Price     OHLC
```

This architecture allows each component to have a clear responsibility and makes the system easier to test and extend.

---

## 13. Future Extensions

The initial Matching Engine can later be extended with:

* Market orders
* Limit orders
* Order cancellation
* Order modification
* Trade IDs
* Timestamps
* Multiple securities
* Trade history
* Market data feeds
* Simulated traders
* Slippage models
* Latency simulation
* Matching-engine performance metrics

These features should be added only after the basic matching mechanism is reliable.

---

## 14. Summary

The Matching Engine answers one fundamental question:

> **Can the best available buyer and seller trade with each other?**

The core rules are:

[
B \geq A
]

[
Q_{\text{trade}}=\min(Q_{\text{buy}},Q_{\text{sell}})
]

and orders follow **price-time priority**.

The Matching Engine repeatedly applies these rules until no compatible orders remain.

For SEE, this component will transform the project from an **Order Book simulator** into an actual **exchange-trading engine**.
