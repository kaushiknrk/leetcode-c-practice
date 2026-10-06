#include <stdio.h>

int minSwaps(char* s) {
    int unmatched_open = 0;
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '[') {
            unmatched_open++;
        } else if (unmatched_open > 0) {
            unmatched_open--;
        }
    }
    
    return (unmatched_open + 1) / 2;
}
