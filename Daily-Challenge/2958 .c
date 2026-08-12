#include <stdlib.h>

typedef struct {
    int key;
    int count;
} Entry;

int maxSubarrayLength(int* nums, int numsSize, int k) {
    int size = numsSize * 2 + 1;
    Entry* table = calloc(size, sizeof(Entry));

    int left = 0;
    int ans = 0;

    for (int right = 0; right < numsSize; right++) {

        int index = (unsigned int)nums[right] % size;

        while (table[index].count != 0 &&
               table[index].key != nums[right]) {
            index = (index + 1) % size;
        }

        table[index].key = nums[right];
        table[index].count++;

        while (table[index].count > k) {

            int removeIndex = (unsigned int)nums[left] % size;

            while (table[removeIndex].key != nums[left]) {
                removeIndex = (removeIndex + 1) % size;
            }

            table[removeIndex].count--;
            left++;
        }

        int length = right - left + 1;

        if (length > ans)
            ans = length;
    }

    free(table);

    return ans;
}
