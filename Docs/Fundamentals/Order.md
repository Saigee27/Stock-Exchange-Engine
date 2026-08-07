# Orders

> **Module:** Market Microstructure
> **Status:** Completed

---

# Overview

An **Order** is a structured instruction submitted by a trader to buy or sell a financial instrument under specific conditions.

An order does **not** represent a completed trade. It simply expresses a trader's intention to participate in the market.

Every transaction executed on a stock exchange begins as an order.

---

# Order vs Trade

These two terms are often confused but represent different stages of the trading process.

| Order | Trade |
|--------|--------|
| A request to buy or sell | A successfully executed transaction |
| Created by a trader | Created by the exchange after matching |
| May remain pending | Immediately updates buyer and seller positions |
| Can be cancelled or modified (depending on rules) | Cannot be reversed by the exchange |

An order becomes a trade **only after** it successfully matches with another compatible order.

---

# Why Orders Exist

Financial markets process millions of requests every day.

Instead of allowing traders to communicate through free-form text, exchanges require every request to follow a standardized structure.

This enables automated validation, efficient processing, fairness, and high-speed execution.

Orders are the primary communication mechanism between traders and exchanges.

---

# Core Components of an Order

Every order contains essential information required by the exchange.

| Field | Purpose |
|---------|---------|
| Order ID | Uniquely identifies an order |
| Trader ID | Identifies the owner of the order |
| Symbol | Financial instrument being traded |
| Side | BUY or SELL |
| Quantity | Number of shares requested |
| Price | Desired execution price |
| Timestamp | Time at which the order was received |

Each field contributes to efficient order management and trade execution.

---

# Order Lifecycle

An order passes through multiple stages before becoming a completed trade.

```text
Order Created
      │
      ▼
Broker Validation
      │
      ▼
Exchange Receives Order
      │
      ▼
Order Book
      │
      ▼
Matching Engine
      │
      ▼
Trade Execution
      │
      ▼
Portfolio Updated
```

Not every order reaches the final stage immediately.

Some remain pending until matching conditions are satisfied.

---

# Price-Time Priority

Most modern electronic exchanges follow the **Price-Time Priority** principle.

Matching decisions are performed in two steps.

### Step 1

Higher BUY prices receive priority.

Lower SELL prices receive priority.

### Step 2

If multiple orders share the same price, the earliest submitted order is executed first.

This ensures both price efficiency and fairness.

---

# Partial Execution

Orders do not need to be completely filled in a single transaction.

Example:

Buyer requests:

```text
BUY

100 Shares

₹3000
```

Seller offers:

```text
SELL

20 Shares

₹3000
```

Execution:

```text
20 Shares Executed

80 Shares Remaining
```

The remaining quantity continues waiting inside the Order Book.

This process is known as **Partial Execution** or **Partial Fill**.

---

# Why Price Has Higher Priority Than Quantity

Exchanges prioritize the **best available price**, not the largest order size.

Example:

| Buyer | Price | Quantity |
|--------|------:|---------:|
| A | ₹3000 | 10 |
| B | ₹2998 | 100 |
| C | ₹2995 | 500 |

A seller enters the market.

The exchange first matches Buyer A because ₹3000 represents the highest buying price.

Only after satisfying the highest-priced orders does the exchange continue matching lower-priced orders.

Price determines **priority**.

Quantity determines **how much** is exchanged.

---

# Engineering Perspective

From a software engineering viewpoint, an order is a structured data object.

Instead of processing unstructured text, exchanges operate on well-defined records containing all required fields.

This design improves:

- Processing speed
- Data consistency
- Validation
- Fault tolerance
- Maintainability

Modern trading systems process millions of these structured objects every trading session.

---

# Computational Perspective

Order processing typically includes:

- Input Validation
- Trader Authentication
- Risk Verification
- Order Routing
- Queue Insertion
- Order Matching
- Trade Reporting

Efficient implementations aim to minimize latency while maintaining correctness and fairness.

---

# New Terminology

- Order
- Trade
- Order ID
- Trader ID
- Symbol
- Side
- Quantity
- Price
- Timestamp
- Price-Time Priority
- Partial Fill
- Pending Order
- Order Lifecycle

---

# Key Takeaways

- An order is a request, not a completed trade.
- Trades occur only after compatible orders are matched.
- Exchanges prioritize better prices before larger quantities.
- Timestamps guarantee fairness between identical prices.
- Orders may be partially executed and remain active until completely filled or cancelled.
- Structured order data enables reliable, high-performance financial systems.