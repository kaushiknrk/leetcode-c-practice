#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int stoneGameII(int* piles, int pilesSize) {
    int n = pilesSize;
    int suff[102];
    memset(suff, 0, sizeof(suff));
    for (int i = n - 1; i >= 0; i--) {
        suff[i] = suff[i + 1] + piles[i];
    }
    
    int dp[102][102];
    memset(dp, 0, sizeof(dp));
    
    for (int i = n - 1; i >= 0; i--) {
        for (int m = 1; m <= n; m++) {
            if (i + 2 * m >= n) {
                dp[i][m] = suff[i];
            } else {
                for (int x = 1; x <= 2 * m; x++) {
                    int val = suff[i] - dp[i + x][max(m, x)];
                    if (val > dp[i][m]) {
                        dp[i][m] = val;
                    }
                }
            }
        }
    }
    return dp[0][1];
}
