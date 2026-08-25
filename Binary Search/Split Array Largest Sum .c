#include <stdio.h>
#include <stdbool.h>

bool canSplit(int* nums, int numsSize, int k, long long max_sum) {
    long long current_sum = 0;
    int subarrays_count = 1;
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max_sum) {
            return false;
        }
        
        if (current_sum + nums[i] > max_sum) {
            subarrays_count++;
            current_sum = nums[i];
            
            if (subarrays_count > k) {
                return false;
            }
        } else {
            current_sum += nums[i];
        }
    }
    return true;
}

int splitArray(int* nums, int numsSize, int k) {
    long long low = 0;
    long long high = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > low) {
            low = nums[i];
        }
        high += nums[i];
    }
    
    long long ans = high;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        
        if (canSplit(nums, numsSize, k, mid)) {
            ans = mid;         
            high = mid - 1;    
        } else {
            low = mid + 1;     
        }
    }
    
    return (int)ans;
}
