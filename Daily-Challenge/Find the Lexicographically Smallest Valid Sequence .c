#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* validSequence(char* word1, char* word2, int* returnSize) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);

    int* suff = (int*)malloc((len1 + 1) * sizeof(int));
    suff[len1] = 0;

    int j = len2 - 1;
    for (int i = len1 - 1; i >= 0; i--) {
        if (j >= 0 && word1[i] == word2[j]) {
            j--;
        }
        suff[i] = len2 - 1 - j;
    }

    int* result = (int*)malloc(len2 * sizeof(int));
    int word2_idx = 0;
    int used_mismatch = 0;

    for (int i = 0; i < len1 && word2_idx < len2; i++) {
        int rem_word2 = len2 - 1 - word2_idx;

        if (word1[i] == word2[word2_idx]) {
            result[word2_idx] = i;
            word2_idx++;
        } else if (!used_mismatch && suff[i + 1] >= rem_word2) {
            result[word2_idx] = i;
            word2_idx++;
            used_mismatch = 1;
        }
    }

    if (word2_idx == len2) {
        *returnSize = len2;
        free(suff);
        return result;
    }

    *returnSize = 0;
    free(suff);
    free(result);
    return NULL;
}
