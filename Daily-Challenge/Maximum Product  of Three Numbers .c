#include <stdio.h>
#include <limits.h>

int maximumProduct(int* nums, int numsSize) {
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;

    for (int i = 0; i < numsSize; i++) {
        int val = nums[i];

        if (val > max1) {
            max3 = max2;
            max2 = max1;
            max1 = val;
        } else if (val > max2) {
            max3 = max2;
            max2 = val;
        } else if (val > max3) {
            max3 = val;
        }

        if (val < min1) {
            min2 = min1;
            min1 = val;
        } else if (val < min2) {
            min2 = val;
        }
    }

    long long prod1 = (long long)max1 * max2 * max3;
    long long prod2 = (long long)min1 * min2 * max1;

    return (prod1 > prod2) ? prod1 : prod2;
}
