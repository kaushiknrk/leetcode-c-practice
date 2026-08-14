#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maximumLengthSubstring(char* s) {
    int len = strlen(s);
    int count[26] = {0};
    int left = 0;
    int max_len = 0;

    for (int right = 0; right < len; right++) {
        int char_idx = s[right] - 'a';
        count[char_idx]++;

        while (count[char_idx] > 2) {
            count[s[left] - 'a']--;
            left++;
        }

        max_len = MAX(max_len, right - left + 1);
    }

    return max_len;
}
