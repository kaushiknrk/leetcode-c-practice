#include <string.h>
#include <stdlib.h>
#include <math.h>

char* smallestPalindrome(char* s, int k) {
    int n = strlen(s);
    int counts[26] = {0};
    for (int i = 0; i < n; i++) {
        counts[s[i] - 'a']++;
    }

    int odd_count = 0;
    char mid_char = '\0';
    int half_counts[26] = {0};
    int half_len = 0;

    for (int i = 0; i < 26; i++) {
        if (counts[i] % 2 != 0) {
            odd_count++;
            mid_char = 'a' + i;
        }
        half_counts[i] = counts[i] / 2;
        half_len += half_counts[i];
    }

    if (odd_count > 1) {
        return "";
    }

    double current_log_perms = 0.0;
    for (int i = 1; i <= half_len; i++) {
        current_log_perms += log(i);
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 1; j <= half_counts[i]; j++) {
            current_log_perms -= log(j);
        }
    }

    long long total_perms;
    if (current_log_perms > log(k) + 1e-7) {
        total_perms = (long long)k + 1;
    } else {
        total_perms = (long long)round(exp(current_log_perms));
    }

    if (total_perms < k) {
        return "";
    }

    char* res = (char*)malloc((n + 1) * sizeof(char));
    int curr_k = k;
    int rem_total = half_len;
    int idx = 0;

    for (int i = 0; i < half_len; i++) {
        for (int c_idx = 0; c_idx < 26; c_idx++) {
            if (half_counts[c_idx] == 0) {
                continue;
            }

            double log_perms_choice = current_log_perms + log(half_counts[c_idx]) - log(rem_total);
            long long perms;
            if (log_perms_choice > log(curr_k) + 1e-7) {
                perms = (long long)curr_k + 1;
            } else {
                perms = (long long)round(exp(log_perms_choice));
            }

            if (curr_k <= perms) {
                res[idx++] = 'a' + c_idx;
                current_log_perms = log_perms_choice;
                half_counts[c_idx]--;
                rem_total--;
                break;
            } else {
                curr_k -= perms;
            }
        }
    }

    if (odd_count == 1) {
        res[idx++] = mid_char;
    }

    for (int i = half_len - 1; i >= 0; i--) {
        res[idx++] = res[i];
    }
    res[n] = '\0';

    return res;
}
