#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int minimumPushes(char* word) {
    int freq[26] = {0};
    int len = strlen(word);
    
    for (int i = 0; i < len; i++) {
        freq[word[i] - 'a']++;
    }
    
    qsort(freq, 26, sizeof(int), compare_desc);
    
    int total_pushes = 0;
    
    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0) {
            break; 
        }
        int pushes_per_letter = (i / 8) + 1; 
        total_pushes += freq[i] * pushes_per_letter;
    }
    
    return total_pushes;
}
