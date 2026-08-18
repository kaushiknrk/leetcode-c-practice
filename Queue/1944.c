#include <stdio.h>
#include <stdlib.h>

int* canSeePersonsCount(int* heights, int heightsSize, int* returnSize) {
    *returnSize = heightsSize;
    int* result = (int*)malloc(heightsSize * sizeof(int));
    int* stack = (int*)malloc(heightsSize * sizeof(int));
    int top = -1;

    for (int i = heightsSize - 1; i >= 0; i--) {
        int visibleCount = 0;

        while (top >= 0 && heights[i] > stack[top]) {
            top--;
            visibleCount++;
        }

        if (top >= 0) {
            visibleCount++;
        }

        result[i] = visibleCount;
        top++;
        stack[top] = heights[i];
    }

    free(stack);
    return result;
}
