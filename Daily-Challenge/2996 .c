#include <stdio.h>
#include <stdbool.h>

int missingInteger(int* nums, int numsSize) {
    int prefix_sum = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1] + 1) {
            prefix_sum += nums[i];
        } else {
            break; 
        }
    }

    bool present[1500] = {false};
    for (int i = 0; i < numsSize; i++) {
        present[nums[i]] = true;
    }

    int x = prefix_sum;
    while (x < 1500 && present[x]) {
        x++;
    }

    return x;
}
