#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Element;

int compare(const void* a, const void* b) {
    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    if (e1->val != e2->val) {
        return (e1->val > e2->val) - (e1->val < e2->val); 
    }
    return e1->idx - e2->idx;
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    if (numsSize <= 1 || k <= 0) return false;

    Element* arr = (Element*)malloc(numsSize * sizeof(Element));
    for (int i = 0; i < numsSize; i++) {
        arr[i].val = nums[i];
        arr[i].idx = i;
    }

    qsort(arr, numsSize, sizeof(Element), compare);

    for (int i = 0; i < numsSize - 1; i++) {
        if (arr[i].val == arr[i + 1].val) {
            if (abs(arr[i].idx - arr[i + 1].idx) <= k) {
                free(arr);
                return true;
            }
        }
    }

    free(arr);
    return false;
}
