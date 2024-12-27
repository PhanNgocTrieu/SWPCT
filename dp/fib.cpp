/**
 * @file fib.cpp
 * @brief This file contains the implementation of a function to find the nth Fibonacci number.
 *
 * The Fibonacci sequence is a series of numbers where each number is the sum of the two preceding ones,
 * usually starting with 0 and 1. This program aims to compute the nth Fibonacci number efficiently.
 *
 * Example:
 * - Fibonacci(0) = 0
 * - Fibonacci(1) = 1
 * - Fibonacci(2) = 1
 * - Fibonacci(3) = 2
 * - Fibonacci(4) = 3
 * - Fibonacci(5) = 5
 *
 * The function can be implemented using various methods such as recursion, dynamic programming, or matrix exponentiation.
 */
#include <bits/stdc++.h>
using namespace std;

vector<long long> dp(LONG_MAX, -1);

// Recursive function to compute the nth Fibonacci number
// This complexity is O(2^n)
long long fib(int x) {
    // Base case
    if (x <= 2) {
        return 1;
    }
    return fib(x - 1) + fib(x - 2);
}


// Function to compute the nth Fibonacci number using memoizations
// This complexity is O(n)
long long F(long long n) {
    if (dp[n] != -1) {
        return dp[n];
    }
    long long result = -1;
    if (n <= 2) {
        result = 1;
    }
    else {
        result = F(n - 1) + F(n - 2);
    }
    dp[n] = result;
    // Compute the nth Fibonacci number using the recurrence relation F(n) = F(n - 1) + F(n - 2)
    // Using memoization to store the computed values to avoid recomputation.
    return result;
}

// Function to compute the nth Fibonacci number using bottom-up dynamic programming
// This complexity is O(n)
long long bottom_up(long long n) {
    vector<long long> ldp(n + 1, 0);
    ldp[1] = 1;
    for (int i = 2; i <= n; i++) {
        ldp[i] = ldp[i - 1] + ldp[i - 2];
    }
    return ldp[n];
}

int main() {
    // Test the function with some test cases
    cout << bottom_up(50) << endl;
    return 0;
}