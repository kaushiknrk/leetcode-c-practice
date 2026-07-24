#include <stdio.h>
#include <stdbool.h>

int uniqueXorTriplets(int* nums, int numsSize) {
    bool has_val[4096] = {false};
    bool possible_pair[4096] = {false};
    
    for (int i = 0; i < numsSize; i++) {
        for (int j = i; j < numsSize; j++) {
            possible_pair[nums[i] ^ nums[j]] = true;
        }
    }
    
    for (int p = 0; p < 4096; p++) {
        if (!possible_pair[p]) continue;
        for (int k = 0; k < numsSize; k++) {
            has_val[p ^ nums[k]] = true;
        }
    }
    
    int count = 0;
    for (int v = 0; v < 4096; v++) {
        if (has_val[v]) {
            count++;
        }
    }
    
    return count;
}
