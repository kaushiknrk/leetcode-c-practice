#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int largestRectangleArea(int* heights, int heightsSize) {
    if (heightsSize == 0) return 0;

    int extendedSize = heightsSize + 1;
    int* extendedHeights = (int*)malloc(extendedSize * sizeof(int));
    for (int i = 0; i < heightsSize; i++) {
        extendedHeights[i] = heights[i];
    }
    extendedHeights[heightsSize] = 0; 
    int* stack = (int*)malloc(extendedSize * sizeof(int));
    int top = -1;
    int maxArea = 0;

    for (int i = 0; i < extendedSize; i++) {
        while (top >= 0 && extendedHeights[i] < extendedHeights[stack[top]]) {
            int heightIndex = stack[top--];
            int height = extendedHeights[heightIndex];

            
            int width = (top == -1) ? i : (i - stack[top] - 1);

            maxArea = MAX(maxArea, height * width);
        }
        
        stack[++top] = i;
    }

    free(extendedHeights);
    free(stack);

    return maxArea;
}
