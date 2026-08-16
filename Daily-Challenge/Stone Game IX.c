#include <stdbool.h>
#include <stdlib.h>

bool stoneGameIX(int* stones, int stonesSize) {
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    
    for (int i = 0; i < stonesSize; i++) {
        int rem = stones[i] % 3;
        if (rem == 0) cnt0++;
        else if (rem == 1) cnt1++;
        else cnt2++;
    }
    
    if (cnt0 % 2 == 0) {
        return cnt1 > 0 && cnt2 > 0;
    }
    
        return abs(cnt1 - cnt2) > 2;
}

