
#include <cstdlib>   // std::abort
#include <iostream>  // std::cerr


namespace bank {

struct Account { double balance{0.0}; };

// Depósito: amount > 0
inline void CT5_Deposit(Account& acc, double amount) {
    if (amount <= 0.0) { std::cerr << "deposit amount <= 0\n"; std::abort(); }
    acc.balance += amount;
}

// Saque: amount > 0 e <= balance
inline void CT5_Withdraw(Account& acc, double amount) {
    if (amount <= 0.0) { std::cerr << "withdraw amount <= 0\n"; std::abort(); }
    if (amount > acc.balance) { std::cerr << "insufficient funds\n"; std::abort(); }
    acc.balance -= amount;
}

} // namespace bank
