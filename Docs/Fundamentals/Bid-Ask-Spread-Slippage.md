# Bid-Ask Spread & Slippage

> **Module:** Trading Fundamentals
> **Status:** Completed

---

# Bid-Ask Spread

The Bid-Ask Spread is the difference between the highest price a buyer is willing to pay and the lowest price a seller is willing to accept.

Best Bid = Highest Buy Price  
Best Ask = Lowest Sell Price

---

# Formula

**Spread = Ask Price - Bid Price**

**Mid Price = (Bid Price + Ask Price) / 2**

**Spread % = (Spread / Mid Price) × 100**

---

# Example

Best Bid = ₹145  
Best Ask = ₹148

Spread = 148 - 145  
        = ₹3

Mid Price = (145 + 148) / 2  
          = ₹146.5

Spread % = (3 / 146.5) × 100  
         = 2.05%

The spread represents the price gap between the current best buyer and seller.

---

# Slippage

Slippage is the difference between the expected execution price and the actual execution price.

It can occur when the available quantity at the desired price is insufficient and an order consumes multiple price levels.

### Buy Order

**Slippage = Actual Execution Price - Expected Price**

### Sell Order

**Slippage = Expected Price - Actual Execution Price**

---

# Example

Order Book:

₹100 → 20 shares  
₹101 → 30 shares  
₹102 → 50 shares

A trader wants to buy **40 shares** expecting ₹100.

First 20 shares:

20 × ₹100 = ₹2,000

Remaining 20 shares:

20 × ₹101 = ₹2,020

Therefore:

Expected Cost = 40 × ₹100  
              = ₹4,000

Actual Cost = ₹2,000 + ₹2,020  
            = ₹4,020

---

# Total Slippage

**Total Slippage = Actual Cost - Expected Cost**

Total Slippage = ₹4,020 - ₹4,000  
               = ₹20

---

# Average Execution Price

**Average Execution Price = Actual Cost / Quantity**

Average Execution Price = ₹4,020 / 40  
                       = ₹100.50

---

# Slippage Per Share

**Slippage Per Share = Average Execution Price - Expected Price**

Slippage Per Share = ₹100.50 - ₹100  
                   = ₹0.50

---

# Slippage Percentage

**Slippage % = |Actual Price - Expected Price| / Expected Price × 100**

For the example:

Slippage % = |100.50 - 100| / 100 × 100  
           = 0.5%

Large orders can consume multiple order-book levels, increasing the average execution price and creating slippage.

---

# Mathematical Relationships

**Spread = Ask - Bid**

**Mid Price = (Bid + Ask) / 2**

**Spread % = (Spread / Mid Price) × 100**

**Total Slippage = Actual Cost - Expected Cost**

**Average Execution Price = Actual Cost / Quantity**

**Slippage Per Share = Average Execution Price - Expected Price**

---

# SEE Application

Order  
↓  
Order Book  
↓  
Available Liquidity  
↓  
Execution  
↓  
Average Execution Price  
↓  
Slippage

The bid-ask spread represents the current gap between buyers and sellers, while slippage measures the additional execution cost caused by insufficient liquidity or movement across multiple price levels.

---

# New Terminology

- Bid-Ask Spread
- Best Bid
- Best Ask
- Mid Price
- Slippage
- Average Execution Price
- Liquidity

---

# Key Takeaways

- The bid is the highest current buy price.
- The ask is the lowest current sell price.
- The spread is the difference between the ask and bid.
- The mid price is the average of the bid and ask.
- Slippage occurs when actual execution differs from the expected price.
- Large orders can consume multiple price levels and create slippage.
- Slippage directly affects trading execution cost and P&L.