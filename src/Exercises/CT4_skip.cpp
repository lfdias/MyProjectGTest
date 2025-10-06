#pragma once
#include <stdexcept>
#include <string>

namespace bank
{

// -----------------------------
// Declarations
// -----------------------------

// Simple Account struct with owner name and balance
struct Account
{
    std::string owner;
    double balance{0.0};
};

// Predicate: checks if amount is positive
bool CT4_IsPositiveAmount(double a);

// Deposit money: amount must be > 0
void CT4_deposit(Account& acc, double amount);

// Withdraw money: amount must be > 0 and <= balance
void CT4_withdraw(Account& acc, double amount);

// Transfer money: withdraw from one account, deposit to another
void CT4_transfer(Account& from, Account& to, double amount);

// Apply simple interest
double CT4_apply_simple_interest(double principal, double rate, int days);

// -----------------------------
// Implementations
// -----------------------------

inline bool CT4_IsPositiveAmount(double a)
{
    return a > 0.0;
}

inline void CT4_deposit(Account& acc, double amount)
{
    if (amount <= 0.0)
    {
        throw std::invalid_argument("amount <= 0");
    }
    acc.balance += amount;
}

inline void CT4_withdraw(Account& acc, double amount)
{
    if (amount <= 0.0)
    {
        throw std::invalid_argument("amount <= 0");
    }
    if (amount > acc.balance)
    {
        throw std::runtime_error("insufficient");
    }
    acc.balance -= amount;
}

inline void CT4_transfer(Account& from, Account& to, double amount)
{
    CT4_withdraw(from, amount);
    CT4_deposit(to, amount);
}

inline double CT4_apply_simple_interest(double principal, double rate, int days)
{
    if (principal < 0.0)
    {
        throw std::invalid_argument("principal < 0");
    }
    if (rate < 0.0 || rate > 1.0)
    {
        throw std::invalid_argument("rate out of range");
    }
    if (days < 0)
    {
        throw std::invalid_argument("days < 0");
    }

    // simple interest: P * (1 + r * t), where t = days / 365.0
    return principal * (1.0 + rate * (days / 365.0));
}

} // namespace bank
