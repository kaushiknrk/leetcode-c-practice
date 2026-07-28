#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 5001
#define MAX_WORD_LEN 31

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    *returnSize = 0;
    if (!s || wordsSize == 0) return NULL;

    int s_len = strlen(s);
    int word_len = strlen(words[0]);
    int total_len = wordsSize * word_len;
    if (s_len < total_len) return NULL;

    int* result = (int*)malloc(s_len * sizeof(int));
    int target_counts[MAX_WORDS] = {0};
    int current_counts[MAX_WORDS] = {0};

    for (int i = 0; i < wordsSize; i++) {
        target_counts[i] = 1;
        for (int j = 0; j < i; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                target_counts[j]++;
                target_counts[i] = 0;
                break;
            }
        }
    }

    for (int i = 0; i < word_len; i++) {
        int left = i;
        int count = 0;
        memset(current_counts, 0, sizeof(current_counts));

        for (int j = i; j <= s_len - word_len; j += word_len) {
            int match_idx = -1;
            for (int k = 0; k < wordsSize; k++) {
                if (target_counts[k] > 0 && strncmp(s + j, words[k], word_len) == 0) {
                    match_idx = k;
                    break;
                }
            }

            if (match_idx != -1) {
                current_counts[match_idx]++;
                count++;

                while (current_counts[match_idx] > target_counts[match_idx]) {
                    int left_idx = -1;
                    for (int k = 0; k < wordsSize; k++) {
                        if (target_counts[k] > 0 && strncmp(s + left, words[k], word_len) == 0) {
                            left_idx = k;
                            break;
                        }
                    }
                    current_counts[left_idx]--;
                    count--;
                    left += word_len;
                }

                if (count == wordsSize) {
                    result[(*returnSize)++] = left;
                }
            } else {
                memset(current_counts, 0, sizeof(current_counts));
                count = 0;
                left = j + word_len;
            }
        }
    }

    return result;
}
