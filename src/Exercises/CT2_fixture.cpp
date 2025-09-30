// Exercise 2 — Minimal bank example (SUT: System Under Test)
// We keep this in a .cpp on purpose (no header). The test file will include it.

#include <stdexcept>
#include <string>

namespace bank {

class BankAccount {
public:
    BankAccount(std::string owner, double initial)
      : owner_(std::move(owner)), balance_(initial) {
        if (owner_.empty()) throw std::invalid_argument("owner empty");
        if (initial < 0)   throw std::invalid_argument("negative initial");
    }

    double Balance() const { return balance_; }

    void Deposit(double amount) {
        if (amount <= 0) throw std::invalid_argument("deposit <= 0");
        balance_ += amount;
    }

    void Withdraw(double amount) {
        if (amount <= 0)            throw std::invalid_argument("withdraw <= 0");
        if (amount > balance_)      throw std::invalid_argument("insufficient funds");
        balance_ -= amount;
    }

private:
    std::string owner_;
    double balance_;
};

} // namespace bank
