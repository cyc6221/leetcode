class Solution {

public:

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

    bool checkPrimeFrequency(vector<int>& nums) {
        int N = 100;
        sieve(N);

        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        for (auto it : freq) {
            int count = it.second;
            if (count <= N && is_prime[count]) {
                return true;
            }
        }

        return false;
    }
};
