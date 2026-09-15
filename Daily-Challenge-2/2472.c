#include <string.h>
#include <stdbool.h>

bool isPalindrome(const char* s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int maxPalindromes(char* s, int k) {
    int n = strlen(s);
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++) {
        if (dp[i] > dp[i + 1]) {
            dp[i + 1] = dp[i];
        }

        if (i - k + 1 >= 0) {
            if (isPalindrome(s, i - k + 1, i)) {
                int option = dp[i - k + 1] + 1;
                if (option > dp[i + 1]) {
                    dp[i + 1] = option;
                }
            }
        }

        if (i - k >= 0) {
            if (isPalindrome(s, i - k, i)) {
                int option = dp[i - k] + 1;
                if (option > dp[i + 1]) {
                    dp[i + 1] = option;
                }
            }
        }
    }

    return dp[n];
}
