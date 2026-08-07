#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int digit_factors[10][4] = {
    {0, 0, 0, 0}, // 0
    {0, 0, 0, 0}, // 1
    {1, 0, 0, 0}, // 2
    {0, 1, 0, 0}, // 3
    {2, 0, 0, 0}, // 4
    {0, 0, 1, 0}, // 5
    {1, 1, 0, 0}, // 6
    {0, 0, 0, 1}, // 7
    {3, 0, 0, 0}, // 8
    {0, 2, 0, 0}  // 9
};

int get_min_suffix_len(int c2, int c3, int c5, int c7, int* digit_counts) {
    if (c2 < 0) c2 = 0;
    if (c3 < 0) c3 = 0;
    if (c5 < 0) c5 = 0;
    if (c7 < 0) c7 = 0;

    memset(digit_counts, 0, 10 * sizeof(int));
    digit_counts[7] = c7;
    digit_counts[5] = c5;

    int cnt8 = c2 / 3;
    int rem2 = c2 % 3;
    int cnt9 = c3 / 2;
    int rem3 = c3 % 2;

    int cnt4 = rem2 / 2;
    int rem2_final = rem2 % 2;

    int cnt6 = 0;
    if (rem2_final == 1 && rem3 == 1) {
        rem2_final = 0;
        rem3 = 0;
        cnt6 = 1;
    }
    if (rem3 == 1 && cnt4 == 1) {
        rem2_final = 1;
        cnt6 = 1;
        rem3 = 0;
        cnt4 = 0;
    }

    digit_counts[8] = cnt8;
    digit_counts[9] = cnt9;
    digit_counts[6] = cnt6;
    digit_counts[4] = cnt4;
    digit_counts[3] = rem3;
    digit_counts[2] = rem2_final;

    int total = 0;
    for (int i = 2; i <= 9; i++) {
        total += digit_counts[i];
    }
    return total;
}

char* smallestNumber(char* num, long long t) {
    long long temp_t = t;
    int target_factors[4] = {0, 0, 0, 0};
    int primes[4] = {2, 3, 5, 7};

    for (int i = 0; i < 4; i++) {
        while (temp_t % primes[i] == 0) {
            temp_t /= primes[i];
            target_factors[i]++;
        }
    }
    if (temp_t > 1) {
        char* res = (char*)malloc(3 * sizeof(char));
        strcpy(res, "-1");
        return res;
    }

    int n = strlen(num);
    
    int prefix_factors[4] = {0, 0, 0, 0};
    int first_zero = -1;
    for (int i = 0; i < n; i++) {
        int d = num[i] - '0';
        if (d == 0) {
            if (first_zero == -1) first_zero = i;
        } else {
            for (int j = 0; j < 4; j++) {
                prefix_factors[j] += digit_factors[d][j];
            }
        }
    }
    if (first_zero == -1) {
        int satisfied = 1;
        for (int j = 0; j < 4; j++) {
            if (prefix_factors[j] < target_factors[j]) {
                satisfied = 0;
                break;
            }
        }
        if (satisfied) {
            char* res = (char*)malloc((n + 1) * sizeof(char));
            strcpy(res, num);
            return res;
        }
    }

    int limit = (first_zero != -1) ? first_zero : n - 1;
    int suffix_counts[10];

    for (int i = n - 1; i >= 0; i--) {
        int d = num[i] - '0';
        
        if (d > 0) {
            for (int j = 0; j < 4; j++) {
                prefix_factors[j] -= digit_factors[d][j];
            }
        }
        
        if (i > limit) continue;

        for (int bigger_d = d + 1; bigger_d <= 9; bigger_d++) {
            int needed[4];
            for (int j = 0; j < 4; j++) {
                needed[j] = target_factors[j] - prefix_factors[j] - digit_factors[bigger_d][j];
            }

            int available_space = n - 1 - i;
            int required_space = get_min_suffix_len(needed[0], needed[1], needed[2], needed[3], suffix_counts);

            if (required_space <= available_space) {
                char* res = (char*)malloc((n + 1) * sizeof(char));
                strncpy(res, num, i);
                res[i] = bigger_d + '0';
                
                int idx = i + 1;
                int padding_ones = available_space - required_space;
                while (padding_ones-- > 0) {
                    res[idx++] = '1';
                }
                for (int dig = 2; dig <= 9; dig++) {
                    for (int c = 0; c < suffix_counts[dig]; c++) {
                        res[idx++] = dig + '0';
                    }
                }
                res[idx] = '\0';
                return res;
            }
        }
    }
    int required_space = get_min_suffix_len(target_factors[0], target_factors[1], target_factors[2], target_factors[3], suffix_counts);
    int new_len = (n + 1 > required_space) ? n + 1 : required_space;
    
    char* res = (char*)malloc((new_len + 1) * sizeof(char));
    int idx = 0;
    int padding_ones = new_len - required_space;
    while (padding_ones-- > 0) {
        res[idx++] = '1';
    }
    for (int dig = 2; dig <= 9; dig++) {
        for (int c = 0; c < suffix_counts[dig]; c++) {
            res[idx++] = dig + '0';
        }
    }
    res[idx] = '\0';
    return res;
}
