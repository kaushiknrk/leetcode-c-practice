#include <stdlib.h>

long long* resultArray(int* nums, int numsSize, int k, int* returnSize) {
    long long* ans = (long long*)calloc(k, sizeof(long long));
    *returnSize = k;
    
    long long dp[5] = {0}; 
    
    for (int i = 0; i < numsSize; i++) {
        long long newDp[5] = {0};
        int numMod = nums[i] % k;
        
        newDp[numMod] = 1;
        
        for (int r = 0; r < k; r++) {
            if (dp[r] > 0) {
                int nextMod = (r * numMod) % k;
                newDp[nextMod] += dp[r];
            }
        }
        
        for (int r = 0; r < k; r++) {
            ans[r] += newDp[r];
            dp[r] = newDp[r];
        }
    }
    
    return ans;
}
