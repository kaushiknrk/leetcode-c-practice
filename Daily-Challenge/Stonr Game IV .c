#include <stdbool.h>

bool winnerSquareGame(int n) {
    bool dp[n + 1];
    
    dp[0] = false;
    
    for (int i = 1; i <= n; i++) {
        dp[i] = false; 
        
        for (int k = 1; k * k <= i; k++) {
            if (!dp[i - k * k]) {
                dp[i] = true;
                break; 
            }
        }
    }
    
    return dp[n];
}
