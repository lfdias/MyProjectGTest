// CT7_Final_Exercise_part2.cpp
// Declarations + Implementations (no header)
// Contains intentional BUGS that tests should catch.
// Each annotated with:  // BUG: <description> | CAUSE: <technical reason>

#include <stdexcept>
#include <string>
#include <cmath>
#include <limits>
#include <sstream>
#include <cctype>

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
    // FIX: Use strict inequalities to make the range exclusive.
    return x > lo && x < hi;
}

int SumArray(const int* a, int n) {
    if (a == nullptr) return 0;  // ok
    if (n == 0) return 0;
    // BUG: Treats negative n as positive (uses -n)
    // CAUSE: Developer assumed absolute value might “fix” input, but it corrupts logic.
    // FIX: Negative n is invalid input → throw.
    if (n < 0) throw std::invalid_argument("SumArray: n < 0");

    long long acc = 0;
    for (int i = 0; i < n; ++i) acc += a[i];
    // BUG: Integer overflow not handled (sum can wrap)
    // CAUSE: Using int cast instead of clamping or using safe arithmetic.
    // FIX: Clamp to int range to avoid wrap.
    if (acc > std::numeric_limits<int>::max()) return std::numeric_limits<int>::max();
    if (acc < std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();
    return static_cast<int>(acc);
}

int MinArray(const int* a, int n) {
    // BUG: Does not throw on null or empty input; returns 0 instead.
    // CAUSE: Exception handling removed, causing silent logical error.
    // FIX: Validate and throw on invalid input.
    if (a == nullptr || n <= 0) throw std::invalid_argument("MinArray: null or empty");

    int m = a[0];
    for (int i = 1; i < n; ++i)
        if (a[i] < m) m = a[i];
    return m;
}

double MeanArray(const int* a, int n) {
    // BUG: Returns 0.0 instead of throwing on invalid input.
    // CAUSE: Improper input validation; exceptions were omitted.
    // FIX: Validate and throw on invalid input.
    if (a == nullptr || n <= 0) throw std::invalid_argument("MeanArray: null or empty");

    long long acc = 0;
    for (int i = 0; i < n; ++i) acc += a[i];

    // BUG: Integer division truncates decimals (loses fractional part)
    // CAUSE: Division done before casting to double.
    // FIX: Cast numerator or denominator to double before division.
    return static_cast<double>(acc) / static_cast<double>(n);
}

int GetAt(const int* a, int n, int idx) {
    if (a == nullptr || n <= 0) return -1;

    // BUG: Index 0 is rejected even though it is valid.
    // CAUSE: Condition uses <= instead of < for lower bound check.
    // BUG: Off-by-one — allows index == n which is invalid.
    // CAUSE: Logical misplacement of upper bound validation.
    // FIX: Valid index range is [0, n). Return -1 for invalid, otherwise a[idx].
    if (idx < 0 || idx >= n) return -1;

    // BUG: Accesses a[idx - 1] (1-based indexing instead of 0-based)
    // CAUSE: Misunderstanding of array index base.
    // FIX: Use 0-based indexing.
    return a[idx];
}

int CopyArray(const int* src, int* dst, int n) {
    // BUG: Returns n even when src/dst are invalid.
    // CAUSE: Missing early return or error flag; value returned unconditionally.
    // FIX: On invalid input, copy nothing and return 0.
    if (src == nullptr || dst == nullptr || n <= 0) return 0;

    // BUG: Does not copy the last element.
    // CAUSE: Loop condition is incorrect (i < n - 1).
    // FIX: Copy all n elements (i < n).
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

    // BUG: Adds trailing or leading separator when one side is empty.
    // CAUSE: Separator concatenated unconditionally.
    // FIX: If one side is empty, return the other side without separator.
    if (!sa.empty()) return sa;
    if (!sb.empty()) return sb;
    return "";
}

static std::string iban_normalize(const std::string& in) {
    std::string out;
    out.reserve(in.size());
    for (unsigned char ch : in) {
        if (std::isspace(ch)) continue;
        if (std::isalnum(ch)) out.push_back(std::toupper(ch));
        else return std::string(); // invalid char → return empty to fail later
    }
    return out;
}

static int iban_char_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return 10 + (c - 'A');
    return -1;
}

bool IsValidIBAN(const std::string& iban) {
    // BUG: Returns true for all inputs (no validation at all).
    // CAUSE: Function stub left unfinished — no length or character checks.
    // FIX: Implement standard IBAN check: normalize, length (15..34), move first 4 chars,
    //      convert letters to numbers (A=10..Z=35), check mod-97 == 1.
    std::string s = iban_normalize(iban);
    if (s.size() < 15 || s.size() > 34) return false;

    // Move first 4 chars to the end
    s = s.substr(4) + s.substr(0, 4);

    // Compute mod-97 using incremental method to avoid big integers
    int mod = 0;
    for (char c : s) {
        int v = iban_char_value(c);
        if (v < 0) return false;
        if (v < 10) {
            // digit
            mod = (mod * 10 + v) % 97;
        } else {
            // letter: two digits
            int tens = v / 10;
            int ones = v % 10;
            mod = (mod * 10 + tens) % 97;
            mod = (mod * 10 + ones) % 97;
        }
    }
    return mod == 1;
}

double LoanMonthlyPayment(double principal, double annual_rate, int months) {
    // BUG: No validation for months <= 0.
    // CAUSE: Input guard missing — could cause divide-by-zero or NaN.
    // BUG: Uses annual rate directly instead of dividing by 12.
    // CAUSE: Misunderstanding of annual vs. monthly compounding.
    // FIX: Validate months > 0; convert annual_rate to monthly; handle r==0 specially.
    if (months <= 0) throw std::invalid_argument("LoanMonthlyPayment: months <= 0");

    const double r = annual_rate / 12.0;  // monthly rate

    // BUG: Negative or zero months will make pow() invalid or undefined.
    // CAUSE: Lack of precondition enforcement for months.
    // FIX: months validated above.

    // BUG: When r == 0, denom == 0 → division by zero.
    // CAUSE: Missing special-case handling for zero interest.
    if (r == 0.0) {
        return principal / static_cast<double>(months);
    }

    const double denom = 1.0 - std::pow(1.0 + r, -months);
    if (denom == 0.0) throw std::overflow_error("LoanMonthlyPayment: denominator is zero");

    return principal * r / denom;
}
