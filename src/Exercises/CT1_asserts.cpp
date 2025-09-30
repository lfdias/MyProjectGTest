#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>

namespace bank {

class BankAccount {
public:
    BankAccount(std::string owner, double initial)
        : owner_(std::move(owner)), balance_(initial) {
        if (balance_ < 0) throw std::invalid_argument("negative initial balance");
        if (owner_.empty()) throw std::invalid_argument("owner empty");
    }

    const std::string& Owner() const { return owner_; }
    const char* OwnerCStr() const { return owner_.c_str(); } // for EXPECT_STREQ/EXPECT_STRNE
    double Balance() const { return balance_; }

    void Deposit(double amount) {
        if (amount <= 0) throw std::invalid_argument("deposit must be positive");
        balance_ += amount;
    }

    void Withdraw(double amount) {
        if (amount <= 0) throw std::invalid_argument("withdraw must be positive");
        if (amount > balance_) throw std::invalid_argument("insufficient funds");
        balance_ -= amount;
    }

    double ApplyMonthlyInterest(double rate) {
        if (rate < 0) throw std::invalid_argument("rate < 0");
        balance_ += balance_ * rate;
        return balance_;
    }

    static double MonthlyFeeFor(double balance) {
        if (balance < 0) throw std::invalid_argument("negative");
        if (balance < 1000) return 5.0;
        if (balance < 5000) return 2.5;
        return 0.0;
    }

    // Very basic IBAN check: 2 letters + minimum length
    static bool IsValidIbanBasic(const std::string& iban) {
        return iban.size() >= 12 &&
               std::isalpha((unsigned char)iban[0]) &&
               std::isalpha((unsigned char)iban[1]);
    }

    // Tiny helper to demo EXPECT_FLOAT_EQ
    static float Half(float x) { return 0.5f * x; }

private:
    std::string owner_;
    double balance_;
};

} // namespace bank
