#include <stdio.h>

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

long long countMultiples(long long mid, int* coins, int coinsSize) {
    long long total = 0;
    int numSubsets = 1 << coinsSize; 
    for (int i = 1; i < numSubsets; ++i) {
        long long current_lcm = 1;
        int subset_size = 0;
        int skip = 0;

        for (int j = 0; j < coinsSize; ++j) {
          
            if ((i >> j) & 1) {
                current_lcm = lcm(current_lcm, coins[j]);
                subset_size++;
                
                
                if (current_lcm > mid) {
                    skip = 1;
                    break;
                }
            }
        }

        if (!skip) {
        
            if (subset_size % 2 == 1) {
                total += mid / current_lcm;
            } else {
                total -= mid / current_lcm;
            }
        }
    }
    return total;
}


long long findKthSmallest(int* coins, int coinsSize, int k) {
   
    long long min_coin = coins[0];
    for (int i = 1; i < coinsSize; ++i) {
        if (coins[i] < min_coin) {
            min_coin = coins[i];
        }
    }

   
    long long low = 1;
    long long high = min_coin * k;
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        
        if (countMultiples(mid, coins, coinsSize) >= k) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1; 
        }
    }
    return ans;
}

