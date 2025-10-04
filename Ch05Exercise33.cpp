// Ch05Exercise33.cpp
// CS310 - Chapter 5, Programming Exercise 33
// Kristoffer Carlino

#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using i64 = long long;

// S(k): cumulative minutes needed for k dishes.
static inline long double sum_time(i64 k, i64 a, i64 b) {
    // S(k) = k/2 * (2a + (k - 1)b)
    return static_cast<long double>(k) *
        (2.0L * static_cast<long double>(a) +
            static_cast<long double>(k - 1) * static_cast<long double>(b)) / 2.0L;
}


static i64 max_dishes(i64 a, i64 b, i64 t) {
    if (t <= 0 || a <= 0) return 0;       // no time or invalid base time → no dishes
    if (b == 0) return t / a;             // constant cost per dish

    // Solve: (b/2)k^2 + ((2a - b)/2)k - t <= 0
    // Positive root (after multiplying both sides by 2):
    //   k = floor( ( - (2a - b) + sqrt((2a - b)^2 + 8bt) ) / (2b) )
    const long double two_a_minus_b = 2.0L * static_cast<long double>(a) - static_cast<long double>(b);
    const long double disc = two_a_minus_b * two_a_minus_b
        + 8.0L * static_cast<long double>(b) * static_cast<long double>(t);
    long double k_root = (-two_a_minus_b + std::sqrt(disc)) / (2.0L * static_cast<long double>(b));

    i64 k = static_cast<i64>(std::floor(k_root));
    if (k < 0) k = 0;

    // Fix result against round-off: back off if too large, increase if room remains.
    while (k > 0 && sum_time(k, a, b) > static_cast<long double>(t)) --k;
    while (sum_time(k + 1, a, b) <= static_cast<long double>(t)) ++k;

    return k;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b, t;
    cout << "Enter a (first dish minutes), b (extra minutes per dish), and t (total minutes): ";
    if (!(cin >> a >> b >> t)) {
        std::cerr << "Input error: please enter three non-negative integers.\n";
        return 1;
    }
    if (a < 0 || b < 0 || t < 0) {
        std::cerr << "Invalid input: a, b, and t must be non-negative.\n";
        return 1;
    }

    const i64 result = max_dishes(a, b, t);
    cout << result << " dish" << (result == 1 ? "" : "es") << '\n';


    return 0;
}
