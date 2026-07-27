#include <stdio.h>
#include <limits.h>

int maxProduct(int* nums, int numsSize) {
    int max1 = INT_MIN, max2 = INT_MIN;
   
    for (int i = 0; i < numsSize; i++) {
        int val = nums[i];

        if (val > max1) {
            max2 = max1;
            max1 = val;
        } else if (val > max2) {
            max2 = val;
        } 

    }
    max1=max1 -1;
    max2=max2 -1;
    long long prod1 = (long long)max1 * max2;
    return prod1;
}
