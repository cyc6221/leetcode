#include <bits/stdc++.h>
using namespace std;

// Maximum number to sieve (adjust as needed for your problem constraints)
#define MAXN 1000005

// Bitset for efficient prime marking (true = prime)
bitset<MAXN> is_prime;

// Optional: list of primes in ascending order
vector<int> primes;

// Classic Sieve of Eratosthenes using bitset
void sieve(int N) {
    is_prime.set();            // Set all bits to true
    is_prime[0] = is_prime[1] = 0;  // 0 and 1 are not primes

    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);  // Store the prime number
            for (int j = i * 2; j <= N; j += i) {
                is_prime[j] = 0;  // Mark multiples of i as non-prime
            }
        }
    }
}

// Example usage (remove I/O for submission templates)
int main() {
    int N = 1e6;       // Change this limit according to problem constraints
    sieve(N);          // Precompute all primes up to N

    int x;
    cin >> x;

    if (x <= N && is_prime[x])
        cout << x << " is a prime number\n";
    else
        cout << x << " is not a prime number\n";

    // Optional: print all primes up to N
    // for (int p : primes) cout << p << " ";

    return 0;
}

// COPY HERE //
#define MAXN 1000005
bitset<MAXN> is_prime;
vector<int> primes;

void sieve(int N) {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;

    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= N; j += i) {
                is_prime[j] = 0;
            }
        }
    }
}
// COPY HERE //