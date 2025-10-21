// CT7_Final_Exercise_part2.cpp
// Declarations + Implementations (no header)
// Fixed (bug-free) versions matching the tests' expected behavior.

#include <stdexcept>
#include <string>
#include <cmath>
#include <limits>
#include <sstream>

// ---------- Declarations (prototypes) ----------
bool    InRangeExclusive(int x, int lo, int hi);

int     SumArray(const int* a, int n);
int     MinArray(const int* a, int n);
double  MeanArray(const int* a, int n);

int     GetAt(const int* a, int n, int idx);           // -1 if invalid/out of range
int     CopyArray(const int* src, int* dst, int n);     // returns number of copied elems

std::string StringJoin2(const char* a, const char* b, const char* sep);

bool    IsValidIBAN(const std::string& iban);          // light validation (length+charset)
double  LoanMonthlyPayment(double principal, double annual_rate, int months);

// ---------- Implementations ----------

bool InRangeExclusive(int x, int lo, int hi) {
    // Exclusive bounds: lo < x < hi
    return x > lo && x < hi;
}

int SumArray(const int* a, int n) {
    if (a == nullptr || n <= 0) return 0;
    long long acc = 0;
    for (int i = 0; i < n; ++i) acc += a[i];
    // Optional safety clamp to int range (harmless for typical inputs)
    if (acc > std::numeric_limits<int>::max()) return std::numeric_limits<int>::max();
    if (acc < std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();
    return static_cast<int>(acc);
}

int MinArray(const int* a, int n) {
    if (a == nullptr || n <= 0) {
        throw std::invalid_argument("MinArray: empty or null");
    }
    int m = a[0];
    for (int i = 1; i < n; ++i) if (a[i] < m) m = a[i];
    return m;
}

double MeanArray(const int* a, int n) {
    if (a == nullptr || n <= 0) {
        throw std::invalid_argument("MeanArray: empty or null");
    }
    long long acc = 0;
    for (int i = 0; i < n; ++i) acc += a[i];
    return static_cast<double>(acc) / static_cast<double>(n);
}

int GetAt(const int* a, int n, int idx) {
    if (a == nullptr || n <= 0 || idx < 0 || idx >= n) return -1;
    return a[idx];
}

int CopyArray(const int* src, int* dst, int n) {
    if (src == nullptr || dst == nullptr || n <= 0) return 0;
    for (int i = 0; i < n; ++i) dst[i] = src[i];
    return n;
}

static inline std::string to_string_safe(const char* s) {
    return s ? std::string(s) : std::string();
}

std::string StringJoin2(const char* a, const char* b, const char* sep) {
    const std::string sa = to_string_safe(a);
    const std::string sb = to_string_safe(b);
    const std::string ssep = to_string_safe(sep);

    if (!sa.empty() && !sb.empty()) return sa + ssep + sb;
    if (!sa.empty()) return sa;
    if (!sb.empty()) return sb;
    return "";
}

bool IsValidIBAN(const std::string& iban) {
    // Minimal validation for tests:
    // - length between 15 and 34
    // - first 2 chars are uppercase letters A-Z
    // - all chars are uppercase alphanumeric (A-Z, 0-9)
    if (iban.size() < 15 || iban.size() > 34) return false;
    auto is_upper_letter = [](char c){ return c >= 'A' && c <= 'Z'; };
    auto is_up_alnum = [](char c){
        return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    };
    if (iban.size() < 2) return false;
    if (!is_upper_letter(iban[0]) || !is_upper_letter(iban[1])) return false;
    for (char c : iban) if (!is_up_alnum(c)) return false;
    return true;
}

double LoanMonthlyPayment(double principal, double annual_rate, int months) {
    if (months <= 0) throw std::invalid_argument("LoanMonthlyPayment: months must be > 0");
    const double r = annual_rate / 12.0;
    if (r == 0.0) return principal / static_cast<double>(months);
    // PMT = P * r / (1 - (1+r)^-n)
    return principal * r / (1.0 - std::pow(1.0 + r, -months));
}
