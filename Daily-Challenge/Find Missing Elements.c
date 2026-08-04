#include <stdio.h>
#include <stdlib.h>

int* findMissingElements(int* nums, int numsSize, int* returnSize) {
    int min = nums[0];
    int max = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < min) min = nums[i];
        if (nums[i] > max) max = nums[i];
    }
    
    int present[101] = {0};
    for (int i = 0; i < numsSize; i++) {
        present[nums[i]] = 1;
    }
    
    int maxMissingCount = (max - min + 1) - numsSize;
    
    if (maxMissingCount <= 0) {
        *returnSize = 0;
        return NULL;
    }
    
    int* missingNums = (int*)malloc(maxMissingCount * sizeof(int));
    int count = 0;
    
    for (int i = min; i <= max; i++) {
        if (present[i] == 0) {
            missingNums[count++] = i;
        }
    }
    
    *returnSize = count;
    return missingNums;
}
