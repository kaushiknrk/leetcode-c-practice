#include <stdlib.h>

int** shiftGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = gridSize;
    int n = gridColSize[0];
    int total = m * n;
    k = k % total;

    *returnSize = m;
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    int** result = (int**)malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        (*returnColumnSizes)[i] = n;
        result[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int old_pos = i * n + j;
            int new_pos = (old_pos + k) % total;
            int new_row = new_pos / n;
            int new_col = new_pos % n;
            result[new_row][new_col] = grid[i][j];
        }
    }

    return result;
}
