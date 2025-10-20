// CT7_Final_Exercise_part2.cpp
// Declarations + Implementations (no header)
// Contains intentional BUGS that tests should catch.
// Each annotated with:  // BUG: <description> | CAUSE: <technical reason>

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

int     GetAt(const int* a, int n, int idx);
int     CopyArray(const int* src, int* dst, int n);

std::string StringJoin2(const char* a, const char* b, const char* sep);

bool    IsValidIBAN(const std::string& iban);
double  LoanMonthlyPayment(double principal, double annual_rate, int months);

// ---------- Implementations (with BUGS) ----------

bool InRangeExclusive(int x, int lo, int hi) {
    // BUG: Returns true when x == lo or x == hi (inclusive)
    // CAUSE: Wrong comparison operators (>= and <= instead of > and <)
    return x >= lo && x <= hi;  
}

int SumArray(const int* a, int n) {
    if (a == nullptr) return 0;  // ok
    if (n == 0) return 0;
    // BUG: Treats negative n as positive (uses -n)
    // CAUSE: Developer assumed absolute value might “fix” input, but it corrupts logic.
    if (n < 0) n = -n;  

    long long acc = 0;
    for (int i = 0; i < n; ++i) acc += a[i];
    // BUG: Integer overflow not handled (sum can wrap)
    // CAUSE: Using int cast instead of clamping or using safe arithmetic.
    return static_cast<int>(acc);  
}

int MinArray(const int* a, int n) {
    // BUG: Does not throw on null or empty input; returns 0 instead.
    // CAUSE: Exception handling removed, causing silent logical error.
    if (a == nullptr || n <= 0) return 0;  

    int m = a[0];
    for (int i = 1; i < n; ++i) 
        if (a[i] < m) m = a[i];
    return m;
}

double MeanArray(const int* a, int n) {
    // BUG: Returns 0.0 instead of throwing on invalid input.
    // CAUSE: Improper input validation; exceptions were omitted.
    if (a == nullptr || n <= 0) return 0.0;    

    long long acc = 0;
    for (int i = 0; i < n; ++i) acc += a[i];

    // BUG: Integer division truncates decimals (loses fractional part)
    // CAUSE: Division done before casting to double.
    return static_cast<double>(acc / n);  
}

int GetAt(const int* a, int n, int idx) {
    if (a == nullptr || n <= 0) return -1;

    // BUG: Index 0 is rejected even though it is valid.
    // CAUSE: Condition uses <= instead of < for lower bound check.
    if (idx <= 0) return -1;  

    // BUG: Off-by-one — allows index == n which is invalid.
    // CAUSE: Logical misplacement of upper bound validation.
    if (idx > n - 1) return -1;

    // BUG: Accesses a[idx - 1] (1-based indexing instead of 0-based)
    // CAUSE: Misunderstanding of array index base.
    return a[idx - 1];  
}

int CopyArray(const int* src, int* dst, int n) {
    // BUG: Returns n even when src/dst are invalid.
    // CAUSE: Missing early return or error flag; value returned unconditionally.
    if (src == nullptr || dst == nullptr || n <= 0) return n;  

    // BUG: Does not copy the last element.
    // CAUSE: Loop condition is incorrect (i < n - 1).
    for (int i = 0; i < n - 1; ++i) dst[i] = src[i];  
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

    // BUG: Adds trailing or leading separator when one side is empty.
    // CAUSE: Separator concatenated unconditionally.
    if (!sa.empty()) return sa + ssep;   // trailing comma
    if (!sb.empty()) return ssep + sb;   // leading comma
    return "";
}

bool IsValidIBAN(const std::string& iban) {
    // BUG: Returns true for all inputs (no validation at all).
    // CAUSE: Function stub left unfinished — no length or character checks.
    (void)iban;
    return true;  
}

double LoanMonthlyPayment(double principal, double annual_rate, int months) {
    // BUG: No validation for months <= 0.
    // CAUSE: Input guard missing — could cause divide-by-zero or NaN.
    // BUG: Uses annual rate directly instead of dividing by 12.
    // CAUSE: Misunderstanding of annual vs. monthly compounding.
    double r = annual_rate;  

    // BUG: Negative or zero months will make pow() invalid or undefined.
    // CAUSE: Lack of precondition enforcement for months.
    double denom = 1.0 - std::pow(1.0 + r, -months);  

    // BUG: When r == 0, denom == 0 → division by zero.
    // CAUSE: Missing special-case handling for zero interest.
    return principal * r / denom;  
}
