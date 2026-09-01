bool predictTheWinner(int* nums, int numsSize) {
    int dp[20][20];
    
    for (int i = 0; i < numsSize; i++) {
        dp[i][i] = nums[i];
    }
    
    for (int len = 2; len <= numsSize; len++) {
        for (int i = 0; i <= numsSize - len; i++) {
            int j = i + len - 1;
            int pickLeft = nums[i] - dp[i + 1][j];
            int pickRight = nums[j] - dp[i][j - 1];
            dp[i][j] = (pickLeft > pickRight) ? pickLeft : pickRight;
        }
    }
    
    return dp[0][numsSize - 1] >= 0;
}
