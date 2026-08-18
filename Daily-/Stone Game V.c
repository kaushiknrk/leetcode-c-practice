#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 501

int dp[MAX_N][MAX_N];
int prefSum[MAX_N];

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int getSum(int left, int right) {
    return prefSum[right + 1] - prefSum[left];
}

int solve(int left, int right, int* stoneValue) {
    if (left == right) {
        return 0;
    }
    
    if (dp[left][right] != -1) {
        return dp[left][right];
    }
    
    int maxScore = 0;
    
    for (int i = left; i < right; i++) {
        int leftSum = getSum(left, i);
        int rightSum = getSum(i + 1, right);
        
        if (leftSum < rightSum) {
            int score = leftSum + solve(left, i, stoneValue);
            maxScore = MAX(maxScore, score);
        } 
        else if (leftSum > rightSum) {
            int score = rightSum + solve(i + 1, right, stoneValue);
            maxScore = MAX(maxScore, score);
        } 
        else {
            int chooseLeft = leftSum + solve(left, i, stoneValue);
            int chooseRight = rightSum + solve(i + 1, right, stoneValue);
            maxScore = MAX(maxScore, MAX(chooseLeft, chooseRight));
        }
    }
    
    return dp[left][right] = maxScore;
}

int stoneGameV(int* stoneValue, int stoneValueSize) {
    memset(dp, -1, sizeof(dp));
    
    prefSum[0] = 0;
    for (int i = 0; i < stoneValueSize; i++) {
        prefSum[i + 1] = prefSum[i] + stoneValue[i];
    }
    
    return solve(0, stoneValueSize - 1, stoneValue);
}
