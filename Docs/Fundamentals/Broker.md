# Broker

> **Module:** Market Infrastructure
> **Status:** Completed

---

# Overview

A Broker is an authorized financial intermediary that provides investors with access to financial markets.

Unlike a Stock Exchange, a broker does not execute trades by matching buyers and sellers. Instead, it acts as a gateway between market participants and the exchange.

Every buy or sell request initiated by an investor is first processed by a broker before reaching the exchange.

---

# Why Do Brokers Exist?

If millions of investors connected directly to the exchange, the exchange would have to manage:

- Customer authentication
- Account management
- Identity verification (KYC)
- Fund management
- Order validation
- Customer support

This would significantly increase system complexity.

Instead, these responsibilities are delegated to brokers, allowing exchanges to focus solely on trade execution and market infrastructure.

---

# Core Responsibilities

A broker typically performs the following tasks:

- Opens trading accounts
- Verifies customer identity (KYC)
- Accepts buy and sell orders
- Validates incoming orders
- Routes orders to the exchange
- Maintains customer portfolios
- Reports executed trades
- Charges brokerage and applicable fees

---

# Trading Workflow

A simplified trading workflow is shown below:

Investor
↓
Broker
↓
Stock Exchange
↓
Matching Engine
↓
Trade Execution

The broker is responsible for forwarding orders, while the exchange is responsible for matching them.

---

# Broker vs Stock Exchange

| Broker | Stock Exchange |
|----------|----------------|
| Customer-facing | Market infrastructure |
| Accepts orders | Matches orders |
| Maintains trading accounts | Maintains order books |
| Performs KYC | Ensures market integrity |
| Routes orders | Executes trades |

---

# System Design Perspective

From a software engineering perspective, a broker functions as an **Order Gateway**.

Its primary objective is to receive client requests, validate them, and forward valid orders to the exchange.

This separation follows the **Single Responsibility Principle (SRP)** by assigning customer-facing operations to brokers while leaving trade execution to the exchange.

---

# Engineering Considerations

Modern brokerage systems prioritize:

- Low latency
- High availability
- Secure authentication
- Fault tolerance
- Reliable order routing
- Efficient account lookup
- Consistent transaction reporting

---

# Performance Goals

| Operation | Target Complexity |
|------------|-------------------|
| Account Lookup | O(1) |
| Authentication | O(1) |
| Portfolio Lookup | O(1) |
| Order Validation | O(1) – O(log n) |
| Order Routing | Constant-time network dispatch (idealized) |

---

# Quantitative Finance Perspective

Although brokers are customer-facing platforms, they play an important role in quantitative trading by providing:

- Market connectivity
- Order routing
- Execution reports
- Portfolio information
- Trade confirmations

Many quantitative trading systems communicate with brokers through APIs to automate trading strategies.


---

# New Terminology

- Broker
- Brokerage
- Trading Account
- Demat Account
- KYC (Know Your Customer)
- Order Gateway
- Order Routing
- Trade Confirmation

---

# Key Takeaways

- Brokers act as intermediaries between investors and exchanges.
- Exchanges execute trades; brokers provide market access.
- Separating broker and exchange responsibilities improves scalability and maintainability.
- Modern brokers are highly optimized software systems designed for secure, reliable, and low-latency communication with financial markets.