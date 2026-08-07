# Order Book Performance & Data Structure Requirements

> **Module:** Market Microstructure / System Engineering  
> **Focus:** Order Book Performance, Algorithmic Complexity & Data Structure Design  
> **Status:** Research / Design Phase

---

# 1. Order Book as a Computational System

An Order Book is a continuously changing data structure containing outstanding BUY and SELL orders for a financial instrument.

Conceptually:

```text
                    ORDER BOOK

SELL SIDE
──────────────────────────────
₹110 → orders
₹108 → orders
₹106 → orders
──────────────────────────────
₹105 → orders
₹103 → orders
₹100 → orders
BUY SIDE
```

The matching engine continuously examines the best available BUY and SELL prices to determine whether a trade can occur.

Therefore, the Order Book is not simply financial data storage.

It is a **high-frequency data processing system**.

---

# 2. Core Operations

An exchange-style Order Book repeatedly performs operations such as:

```text
1. Insert Order
2. Find Best Bid
3. Find Best Ask
4. Match Orders
5. Execute Partial Fills
6. Remove Filled Orders
7. Cancel Orders
8. Update Remaining Quantity
```

The performance of these operations directly affects the efficiency of the matching engine.

---

# 3. Best Bid and Best Ask

The matching engine needs immediate access to the best available prices.

### Best Bid

The highest price currently offered by a buyer.

```text
BUY

₹105  ← Best Bid
₹103
₹100
```

### Best Ask

The lowest price currently offered by a seller.

```text
SELL

₹106  ← Best Ask
₹108
₹110
```

A trade can potentially occur when:

```text
Best Bid >= Best Ask
```

Otherwise, the orders remain in the Order Book.

---

# 4. Naive Array-Based Approach

A simple implementation could store orders in an array or vector.

Example:

```text
BUY ORDERS

₹100
₹105
₹103
₹110
₹99
```

To find the highest bid, the system could scan every order.

```text
Start
  ↓
₹100
  ↓
₹105
  ↓
₹103
  ↓
₹110
  ↓
₹99
  ↓
Highest = ₹110
```

If there are `n` orders, the system may need to inspect all `n` elements.

Therefore:

```text
Time Complexity = O(n)
```

---

# 5. Why O(n) Can Become a Problem

For a small simulation:

```text
n = 100
```

A linear scan is completely acceptable.

However, consider:

```text
n = 100,000
n = 1,000,000
n = 10,000,000
```

If the matching engine repeatedly scans the entire Order Book to find the best price, the amount of computation increases with the number of orders.

A single operation being `O(n)` may become expensive when performed repeatedly.

The important engineering question becomes:

> Can the Order Book be organized so that frequently required information is available without scanning every order?

---

# 6. Complexity and Matching

Suppose a market order arrives and the engine needs to find the best available SELL orders.

A naive approach could be:

```text
Search all SELL orders
        ↓
Find lowest price
        ↓
Execute
        ↓
Search again
        ↓
Find next lowest price
```

Repeated searches can create unnecessary computational work.

A better architecture should make the following operation efficient:

```text
Get Best Ask
```

and similarly:

```text
Get Best Bid
```

This makes **data structure selection** an important part of exchange-engine design.

---

# 7. Price-Time Priority

The Order Book must not only organize orders by price.

Orders at the same price generally follow **time priority**.

Example:

```text
₹100

Order A → timestamp 10:01:01
Order B → timestamp 10:01:03
Order C → timestamp 10:01:07
```

Execution priority:

```text
A
↓
B
↓
C
```

Therefore, the system has two separate ordering requirements:

```text
1. Price Priority
2. Time Priority
```

This creates a hierarchical data organization problem.

---

# 8. Price Levels

Instead of thinking about every order independently, orders can be grouped by price.

Example:

```text
₹105
 ├── Order A
 ├── Order B
 └── Order C

₹103
 ├── Order D
 └── Order E

₹100
 └── Order F
```

Each price represents a **price level**.

Each price level can contain multiple orders.

Conceptually:

```text
Price Level
     ↓
Queue of Orders
```

This structure naturally represents the Price-Time Priority model.

---

# 9. Data Structure Requirements

The Order Book needs to efficiently support two different problems.

### Problem A: Price organization

The system needs to quickly determine:

```text
Highest BUY price
Lowest SELL price
```

### Problem B: Time organization

At the same price, the system needs:

```text
Oldest order
↓
Next order
↓
Next order
```

Therefore, a useful design needs to support:

```text
Price → Ordered Price Levels
Price Level → FIFO Orders
```

This is an important example of why real-world systems often require **combinations of data structures** rather than a single container.

---

# 10. Candidate Data Structures

Different structures provide different performance characteristics.

| Data Structure | Primary Strength |
|---|---|
| Array / Vector | Indexed storage and sequential traversal |
| Queue | FIFO processing |
| Priority Queue | Fast access to highest/lowest priority element |
| Hash Table | Fast average key lookup |
| Ordered Map | Maintains keys in sorted order |

No structure is universally optimal.

The correct choice depends on the operations required by the system.

---

# 11. Complexity Fundamentals

Algorithmic complexity describes how computational work changes as input size increases.

### O(1)

Constant time.

The operation does not depend on the number of elements.

```cpp
arr[3];
```

Conceptually:

```text
10 elements   → one access
1,000 elements → one access
1,000,000 elements → one access
```

---

### O(n)

Linear time.

The amount of work grows approximately with the number of elements.

```cpp
for(int i = 0; i < n; i++)
{
    // process element
}
```

Example:

```text
n = 100
→ ~100 iterations

n = 1,000,000
→ ~1,000,000 iterations
```

---

### O(n²)

Quadratic time.

Often produced by nested loops.

```cpp
for(int i = 0; i < n; i++)
{
    for(int j = 0; j < n; j++)
    {
        // process
    }
}
```

Approximately:

```text
n × n = n²
```

For:

```text
n = 1,000
```

this can mean roughly:

```text
1,000 × 1,000
= 1,000,000 operations
```

This demonstrates why algorithmic complexity becomes increasingly important as system scale increases.

---

# 12. Performance Is About Repeated Operations

An individual `O(n)` operation may not be problematic.

The bigger concern is repeated execution.

For example:

```text
Receive Order
      ↓
Find Best Price → O(n)
      ↓
Execute
      ↓
Find Next Best Price → O(n)
      ↓
Execute
      ↓
Repeat
```

A trading system may process a very large number of orders.

Therefore, reducing the cost of frequently executed operations can have a significant effect on total system performance.

---

# 13. Latency

In electronic trading systems, **latency** refers to the time required for an operation or message to travel through the system.

A simplified trading path is:

```text
Trader
  ↓
Broker
  ↓
Exchange Gateway
  ↓
Order Book
  ↓
Matching Engine
  ↓
Trade
```

The matching engine therefore needs to process orders efficiently.

For this project, latency will initially be treated as a software-performance concept rather than attempting to reproduce real exchange hardware or network infrastructure.

---

# 14. Engineering Trade-Off

A simple implementation is often easier to understand:

```text
Vector
  ↓
Linear Search
  ↓
O(n)
```

An optimized implementation may require more sophisticated structures:

```text
Ordered Price Levels
        +
FIFO Order Queues
        ↓
Efficient Matching
```

However, increased complexity also introduces:

- More difficult implementation
- More edge cases
- More memory considerations
- More complicated cancellation logic
- Greater testing requirements

Therefore:

> **Optimization should be driven by actual system requirements rather than complexity for its own sake.**

---

# 15. Stock Exchange Engine Application

The Stock Exchange Engine will eventually need to maintain:

```text
BUY ORDER BOOK
        +
SELL ORDER BOOK
        ↓
Matching Engine
        ↓
Trade Execution
        ↓
Portfolio / Cash Updates
```

The first implementation can prioritize:

```text
Correctness
    ↓
Clear architecture
    ↓
Testing
    ↓
Performance analysis
    ↓
Optimization
```

This allows the system to evolve from a simple educational simulator into a more sophisticated market simulation.

---

# 16. Future Optimization Path

The Order Book will eventually investigate:

```text
Arrays / Vectors
       ↓
Queue
       ↓
Priority Queue
       ↓
Ordered Map
       ↓
Hashing
       ↓
Composite Data Structures
```

Each stage will be introduced only when the system has a requirement for it.

The objective is not to use the most complicated data structure.

The objective is to choose a structure that provides the required operations with an appropriate computational cost.

---

# 17. Quant / Finance Connection

Order Book performance is closely related to **market microstructure**.

The structure of outstanding orders determines information such as:

```text
Best Bid
Best Ask
Bid-Ask Spread
Available Quantity
Price Levels
Market Depth
Order Imbalance
Liquidity
```

These variables can later become inputs for quantitative analysis.

For example:

```text
Bid Quantity = 500
Ask Quantity = 200

Order Imbalance
= (500 - 200) / (500 + 200)
= 300 / 700
≈ 0.429
```

This indicates substantially greater displayed buying interest than selling interest at the measured levels.

Such measurements can later be incorporated into trading strategies and market simulations.

---

# 18. Key Engineering Insight

The central lesson is:

> **Data structures are selected according to the operations a system needs to perform efficiently.**

For an exchange Order Book, the important requirements are:

```text
Fast price discovery
        +
Price priority
        +
Time priority
        +
Efficient insertion
        +
Efficient removal
        +
Efficient matching
```

The Order Book is therefore both a **financial market structure** and a **data-structure problem**.

---

# 19. Current Design Target

The Stock Exchange Engine will eventually implement:

```text
Order
  ↓
Price Level
  ↓
Order Book
  ↓
Matching Engine
  ↓
Trade
```

The implementation will begin with a simple, understandable architecture and progressively optimize individual components as DSA knowledge and system requirements develop.

---

# Key Takeaways

- An Order Book is a continuously changing computational structure.
- Best Bid and Best Ask are critical values for trade matching.
- Naive linear scanning can produce `O(n)` lookup operations.
- Repeated `O(n)` operations can become expensive at scale.
- Price-Time Priority creates two levels of ordering requirements.
- Orders can be conceptually grouped into price levels.
- FIFO behavior is required within a price level.
- Different data structures optimize different operations.
- Latency and algorithmic complexity are important considerations in electronic trading.
- Optimization should follow measurable requirements rather than complexity for its own sake.
- Order Book data can later become a source of quantitative market-microstructure signals.