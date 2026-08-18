#include <stdio.h>

int largestInteger(int* nums, int numsSize, int k) {
    int count[51] = {0};
    
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    if (k == numsSize) {
        int maxVal = -1;
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] > maxVal) {
                maxVal = nums[i];
            }
        }
        return maxVal;
    }

    if (k == 1) {
        int maxVal = -1;
        for (int i = 0; i <= 50; i++) {
            if (count[i] == 1) {
                maxVal = i;
            }
        }
        return maxVal;
    }

    int firstElement = nums[0];
    int lastElement = nums[numsSize - 1];
    int maxVal = -1;

    if (count[firstElement] == 1) {
        maxVal = firstElement;
    }
    if (count[lastElement] == 1 && lastElement > maxVal) {
        maxVal = lastElement;
    }

    return maxVal;
}
