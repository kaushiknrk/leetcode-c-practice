#include <stdbool.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    bool rows[9][10] = {false};
    bool cols[9][10] = {false};
    bool boxes[9][10] = {false};

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            char val = board[r][c];
            
            if (val == '.') {
                continue;
            }
            
            int num = val - '0';
            int box_index = (r / 3) * 3 + (c / 3);
            
            if (rows[r][num] || cols[c][num] || boxes[box_index][num]) {
                return false;
            }
            
            rows[r][num] = true;
            cols[c][num] = true;
            boxes[box_index][num] = true;
        }
    }
    
    return true;
}
