#include <stdio.h>
#include <stdlib.h>


int* resultArray(int* nums, int numsSize, int* returnSize) {
    int arr1[50];
    int arr2[50];
    
    int size1 = 0;
    int size2 = 0;
    
    arr1[size1++] = nums[0];
    
    arr2[size2++] = nums[1];
    
    for (int i = 2; i < numsSize; i++) {
        if (arr1[size1 - 1] > arr2[size2 - 1]) {
            arr1[size1++] = nums[i];
        } else {
            arr2[size2++] = nums[i];
        }
    }
    
    int* result = (int*)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;
    
    int index = 0;
    for (int i = 0; i < size1; i++) {
        result[index++] = arr1[i];
    }
    for (int i = 0; i < size2; i++) {
        result[index++] = arr2[i];
    }
    
    return result;
}
