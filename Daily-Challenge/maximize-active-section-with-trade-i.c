#include <string.h>
#include <limits.h>

int maxActiveSectionsAfterTrade(const char* s) {
    int n = strlen(s);
    int total_ones = 0;
    int max_zero = 0;
    int min_one = INT_MAX;
    
    int current_zero = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            total_ones++;
            current_zero = 0;
        } else {
            current_zero++;
            if (current_zero > max_zero) max_zero = current_zero;
        }
    }

    int ans = total_ones;

    int i = 0;
    while (i < n) {
        if (s[i] == '1') {
            int start = i;
            while (i < n && s[i] == '1') i++;
            int length = i - start;

            if (start > 0 && i < n) {
                if (length < min_one) min_one = length;

                int left_zeros = 0, l = start - 1;
                while (l >= 0 && s[l] == '0') { left_zeros++; l--; }

                int right_zeros = 0, r = i;
                while (r < n && s[r] == '0') { right_zeros++; r++; }

                int merged_score = total_ones + left_zeros + right_zeros;
                if (merged_score > ans) ans = merged_score;
            }
        } else {
            i++;
        }
    }

    if (max_zero > 0 && min_one != INT_MAX) {
        int swap_score = total_ones + max_zero - min_one;
        if (swap_score > ans) ans = swap_score;
    }

    return ans;
}
