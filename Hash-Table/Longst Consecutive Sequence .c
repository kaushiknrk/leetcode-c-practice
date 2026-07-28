#include <stdlib.h>

int cmp(const void* a, const void* b) {
    long long diff = (long long)*(int*)a - (long long)*(int*)b;
    return (diff > 0) - (diff < 0);
}

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    qsort(nums, numsSize, sizeof(int), cmp);

    int max_len = 1;
    int current_len = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[i - 1]) {
            if (nums[i] == nums[i - 1] + 1) {
                current_len++;
            } else {
                if (current_len > max_len) {
                    max_len = current_len;
                }
                current_len = 1;
            }
        }
    }

    return current_len > max_len ? current_len : max_len;
}
