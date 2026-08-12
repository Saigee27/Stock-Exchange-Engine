# Price Formation & Valuation

> **Module:** Market Fundamentals
> **Status:** Completed

---

# Overview

Stock prices are determined through the interaction between buyers and sellers.

The exchange does not directly decide the price of a stock. Instead, information affects trader expectations, which influence buying and selling decisions. These decisions create orders, which enter the order book and are matched by the exchange.

This process is known as **Price Discovery**.

---

# Price Discovery

Price Discovery is the process through which market participants determine the current market price of a security.

```text
Company Information
        ↓
Trader Expectations
        ↓
Trading Decisions
        ↓
Buy / Sell Orders
        ↓
Order Book
        ↓
Matching Engine
        ↓
Executed Trades
        ↓
Market Price
```

The exchange provides the infrastructure for this process rather than directly assigning the price.

---

# Fundamental Value vs Market Price

| Concept | Meaning |
|---|---|
| Fundamental Value | Estimated value based on financial and economic factors |
| Market Price | Current price determined by market trading |
| Valuation | Process of estimating an asset's value |

Different traders can assign different values to the same company because they have different expectations about its future.

```text
Different Expectations
        ↓
Different Valuations
        ↓
Different Trading Decisions
        ↓
Different Orders
        ↓
Price Discovery
```

---

# Market Capitalization

Market Capitalization represents the total market value of a company's outstanding shares.

### Formula

```text
Market Cap = Share Price × Shares Outstanding
```

### Example

```text
Share Price        = ₹100
Shares Outstanding = 1,000,000

Market Cap = ₹100 × 1,000,000
           = ₹100,000,000
           = ₹10 Crore
```

Share price alone cannot determine the size of a company because the number of outstanding shares also matters.

---

# Earnings Per Share (EPS)

EPS represents the earnings attributable to each outstanding share.

### Formula

```text
EPS = Net Profit / Shares Outstanding
```

### Example

```text
Net Profit         = ₹20,00,000
Shares Outstanding = 1,00,000

EPS = ₹20
```

If profit increases while shares remain constant:

```text
Profit ↑ → EPS ↑
```

If shares increase while profit remains constant:

```text
Shares Outstanding ↑ → EPS ↓
```

---

# Price-to-Earnings Ratio (P/E)

P/E compares the market price of a stock with its earnings per share.

### Formula

```text
P/E = Market Price / EPS
```

### Example

```text
Market Price = ₹100
EPS          = ₹20

P/E = 100 / 20
    = 5×
```

---

# P/E & Market Expectations

P/E is affected by both market price and EPS.

```text
Price ↑
EPS =
P/E ↑
```

```text
Price =
EPS ↑
P/E ↓
```

A high P/E can occur when investors expect strong future earnings growth.

```text
Future Growth Expectations
          ↓
Higher Willingness to Pay
          ↓
Higher Market Price
          ↓
Higher P/E
```

If expected growth fails to occur, investors may revise their valuations and sell.

---

# Good Company ≠ Good Stock

A financially strong company does not automatically mean its stock is attractively priced.

| Company | EPS | Price | P/E |
|---|---:|---:|---:|
| A | ₹20 | ₹100 | 5× |
| B | ₹20 | ₹1,000 | 50× |

Both companies could be strong businesses, but investors are paying much more relative to current earnings for Company B.

The important question is not only:

> "Is this a good company?"

It is also:

> "Is the current market price reasonable relative to its earnings, growth and risk?"

---

# Corporate Events

Corporate events can change trader expectations and therefore influence trading activity.

Examples:

- Earnings Announcements
- Dividends
- Stock Splits
- Mergers
- Acquisitions
- Product Launches
- Management Changes
- Debt Issuance
- Share Buybacks
- Regulatory Events

A realistic exchange should not directly implement:

```text
Good News → Price + ₹50
```

Instead:

```text
Corporate Event
      ↓
Trader Interpretation
      ↓
Trading Decisions
      ↓
Orders
      ↓
Order Book
      ↓
Matching
      ↓
Trades
      ↓
Price Movement
```

This allows price movement to emerge from simulated market behavior.

---

# Order Flow & Price Movement

Price movement is affected by the interaction between orders and available liquidity.

Example:

```text
ASK

₹3010 → 100 shares
₹3005 → 50 shares
₹3000 → 30 shares
```

If buyers consume these sell orders:

```text
Buy ₹3000 → 30 shares
Buy ₹3005 → 50 shares
Buy ₹3010 → 100 shares
```

The next available seller may be at a higher price.

```text
Order Flow
    ↓
Liquidity Consumption
    ↓
Trade Execution
    ↓
Price Movement
```

This mechanism will become important when implementing the SEE matching engine.

---

# Fundamental Data vs Market Data

| Fundamental Data | Market Data |
|---|---|
| Revenue | Bid Price |
| Net Profit | Ask Price |
| Assets | Bid Quantity |
| Liabilities | Ask Quantity |
| Debt | Last Traded Price |
| Cash | Trading Volume |
| Shares Outstanding | Executed Trades |
| EPS | Order Book |
| Corporate Events | Market Depth |

SEE should keep company fundamentals separate from exchange-generated market data.

---

# Source Data vs Derived Data

### Source Data

- Revenue
- Net Profit
- Shares Outstanding
- Trade Price
- Trade Quantity
- Corporate Events

### Derived Data

- EPS
- Market Capitalization
- P/E
- Returns
- Price Change
- Trading Volume

Examples:

```text
Net Profit + Shares Outstanding
            ↓
           EPS
```

```text
Share Price + Shares Outstanding
            ↓
       Market Cap
```

```text
Market Price + EPS
            ↓
           P/E
```

Derived values should be calculated from clearly defined source data instead of maintaining unnecessary duplicate state.

---

# Computational Perspective

Price formation generates continuous market events:

- New Order
- Order Cancellation
- Order Modification
- Trade Execution
- Price Update
- Corporate Event

Each event changes the state of the simulated market.

```text
Market Event
      ↓
State Change
      ↓
Order Book / Market Data Update
```

As the number of orders increases, efficient data structures become important for the matching engine.

---

# Quantitative Finance Perspective

Understanding price formation is fundamental to:

- Market Microstructure
- Order Flow Analysis
- Liquidity Modeling
- Market Impact
- Volatility
- Algorithmic Trading
- High-Frequency Trading
- Execution Algorithms
- Transaction Cost Analysis

SEE can eventually generate market data that can be used for quantitative analysis and trading strategies.

---

# Core Formulas

| Concept | Formula |
|---|---|
| Market Capitalization | `Share Price × Shares Outstanding` |
| EPS | `Net Profit / Shares Outstanding` |
| P/E | `Market Price / EPS` |
| Return | `(Current Price - Previous Price) / Previous Price` |

---

# SEE Architecture

```text
Company
   ↓
Fundamental Data
   ↓
Corporate Events
   ↓
Trader
   ↓
Trading Decisions
   ↓
Orders
   ↓
Order Book
   ↓
Matching Engine
   ↓
Trades
   ↓
Market Data
   ↓
Analytics
```

The key design principle is:

> **Fundamentals influence trader behavior. Trader behavior creates orders. Orders create trades. Trades produce market prices.**

---

# Engineering Considerations

| Component | Responsibility |
|---|---|
| Company | Fundamental information |
| Trader | Trading decisions |
| Order | Trading intent |
| Order Book | Active orders and liquidity |
| Matching Engine | Matches compatible orders |
| Trade | Represents executed transactions |
| Market Data | Represents current market state |
| Analytics | Calculates financial metrics |

---

# New Terminology

- Price Discovery
- Fundamental Value
- Market Price
- Market Capitalization
- Earnings Per Share (EPS)
- Price-to-Earnings Ratio (P/E)
- Market Expectations
- Order Flow
- Liquidity
- Market Impact
- Market Data
- Corporate Event
- Market Microstructure

---

# Further Reading Topics

- Order Books
- Matching Engines
- Market Orders
- Limit Orders
- Bid & Ask
- Bid-Ask Spread
- Liquidity
- Market Makers
- Price Impact
- Volatility
- Returns
- Clearing & Settlement
- Algorithmic Trading
- Market Microstructure

---

# Key Takeaways

- Stock prices emerge from interactions between buyers and sellers.
- Price Discovery is the process through which market prices are formed.
- Market Price and Fundamental Value are not necessarily equal.
- Market Capitalization depends on share price and shares outstanding.
- EPS measures earnings attributable to each share.
- P/E compares market price with EPS.
- P/E changes when either price or EPS changes.
- High P/E can reflect expectations of future growth.
- A good company does not automatically mean a good stock valuation.
- Corporate events influence traders through information and expectations.
- Order flow and liquidity affect price movement.
- Fundamental data and market data should remain separate in SEE.
- Price formation connects financial theory directly to the Order Book and Matching Engine.