#include <stdio.h>
#include <stdbool.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

long long countMultiples(int* coins, int coinsSize, long long target) {
    long long total_count = 0;
    int total_subsets = 1 << coinsSize;

    for (int mask = 1; mask < total_subsets; mask++) {
        long long current_lcm = 1;
        int bits_set = 0;
        
        for (int i = 0; i < coinsSize; i++) {
            if ((mask >> i) & 1) {
                bits_set++;
                current_lcm = lcm(current_lcm, coins[i]);
                if (current_lcm > target) {
                    break;
                }
            }
        }
        
        long long multiples = target / current_lcm;
        
        if (bits_set % 2 == 1) {
            total_count += multiples;
        } else {
            total_count -= multiples;
        }
    }
    
    return total_count;
}

long long findKthSmallest(int* coins, int coinsSize, int k) {
    long long min_coin = coins[0];
    for (int i = 1; i < coinsSize; i++) {
        if (coins[i] < min_coin) {
            min_coin = coins[i];
        }
    }

    long long low = min_coin;
    long long high = min_coin * k;
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        
        if (countMultiples(coins, coinsSize, mid) >= k) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}
