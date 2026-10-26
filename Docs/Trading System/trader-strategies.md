# Trader Strategies

## 1. Overview

The Stock Exchange Engine (SEE) contains multiple automated traders that generate orders during each market round.

Initially, traders generated orders using random decisions:

$$
Trader \rightarrow Random\ Order
$$

This approach allows market activity to be simulated, but all traders behave similarly.

The Trader Strategy system introduces different decision-making behaviours:

$$
Trader \rightarrow Strategy \rightarrow Order
$$

This allows different traders to participate in the market using different strategies.

---

## 2. Strategy Types

The current system defines three trader strategies:

```cpp
enum class TraderStrategy
{
    RANDOM,
    MOMENTUM,
    VALUE
};
```

### 2.1 Random Strategy

The Random strategy generates orders without considering market direction.

The order side is selected randomly:

$$
P(BUY)=P(SELL)=0.5
$$

The quantity is currently generated within the range:

$$
1 \leq Q \leq 20
$$

The selected company is also chosen randomly from the available companies.

Therefore:

$$
Order = f(Random\ Company,\ Random\ Side,\ Current\ Price,\ Random\ Quantity)
$$

This strategy provides baseline market activity.

---

### 2.2 Momentum Strategy

The Momentum strategy is based on the assumption that recent price movement may continue.

If the observed price trend is positive:

$$
\Delta P > 0 \Rightarrow BUY
$$

If the observed price trend is negative:

$$
\Delta P < 0 \Rightarrow SELL
$$

where:

$$
\Delta P = P_t-P_{t-1}
$$

The current implementation establishes the strategy type. More advanced price-history-based momentum logic can be introduced when historical market data becomes available.

---

### 2.3 Value Strategy

The Value strategy attempts to identify whether an asset is relatively cheap or expensive compared with a reference value.

A simplified decision model can be represented as:

$$
P_t < P_{reference} \Rightarrow BUY
$$

$$
P_t > P_{reference} \Rightarrow SELL
$$

where:

* \(P_t\) = current market price
* \(P_{reference}\) = estimated reference/fair value

The current SEE implementation establishes the strategy architecture. More sophisticated valuation models can be added later.

---

## 3. Trader Architecture

Each trader contains:

```text
Trader
├── ID
├── Market Reference
├── Strategy
└── generateOrder()
```

The strategy is represented using:

```cpp
TraderStrategy STRATEGY;
```

The market is stored as a reference:

```cpp
Market& MARKET;
```

The market is shared between traders, while each trader maintains its own strategy.

---

## 4. Order Generation Flow

The order generation process follows:

```text
Trader
   ↓
Select Company
   ↓
Apply Trader Strategy
   ↓
Determine BUY / SELL
   ↓
Use Current Market Price
   ↓
Generate Quantity
   ↓
Create Order
```

The resulting order is then passed into the exchange system.

```text
Trader
   ↓
Order
   ↓
Exchange
   ↓
OrderBook
   ↓
Matching Engine
   ↓
Trade
```

---

## 5. Strategy Representation

Strategies are represented using an enumeration:

```cpp
enum class TraderStrategy
{
    RANDOM,
    MOMENTUM,
    VALUE
};
```

A trader receives its strategy during construction:

```cpp
Trader(int id, Market& market, TraderStrategy strategy)
```

Example:

```cpp
Trader trader1(1, market, TraderStrategy::RANDOM);
Trader trader2(2, market, TraderStrategy::MOMENTUM);
Trader trader3(3, market, TraderStrategy::VALUE);
```

Each trader can therefore behave differently while interacting with the same market.

---

## 6. Design Principle

The primary purpose of the Trader Strategy system is to separate **market participation** from **trader decision-making**.

Without strategies:

$$
Trader \rightarrow Random\ Order
$$

With strategies:

$$
Trader \rightarrow Strategy \rightarrow Order
$$

This separation makes the system easier to extend.

Future strategies can include:

* Mean Reversion
* Trend Following
* Market Making
* Arbitrage
* High-Frequency Trading
* Risk-Based Trading

The existing exchange components do not need to be redesigned when new trader behaviours are introduced.

---

## 7. Current Limitations

The initial strategy system is intentionally simplified.

Current limitations include:

* Limited historical price data
* No portfolio or cash management
* No position tracking
* No risk management
* No transaction costs
* No advanced indicators
* No order-book-aware strategy decisions

These features can be introduced in later stages of the SEE roadmap.

---

## 8. Future Architecture

As the simulation becomes more realistic, the strategy layer can evolve into:

```text
                    Trader
                       │
                 ┌─────┴─────┐
                 │  Strategy  │
                 └─────┬─────┘
                       │
          ┌────────────┼────────────┐
          ↓            ↓            ↓
       Market Data   Portfolio    Risk Model
          │            │            │
          └────────────┼────────────┘
                       ↓
                 Trading Decision
                       ↓
                      Order
                       ↓
                    Exchange
```

This provides a foundation for more advanced algorithmic trading simulation.

---

## 9. Summary

The Trader Strategy system introduces heterogeneous behaviour into the Stock Exchange Engine.

The core relationship is:

$$
\boxed{Trader \rightarrow Strategy \rightarrow Order}
$$

Three initial strategies are defined:

| Strategy   | Primary Behaviour                            |
| ---------- | -------------------------------------------- |
| `RANDOM`   | Random market participation                  |
| `MOMENTUM` | Trades according to price direction          |
| `VALUE`    | Trades according to estimated relative value |

The strategy layer provides the foundation for progressively more realistic automated trading behaviour in future SEE development.
