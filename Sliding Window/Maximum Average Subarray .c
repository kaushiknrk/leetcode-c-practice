double findMaxAverage(int* nums, int numsSize, int k) {
    double currentWindowSum = 0;
    for (int i = 0; i < k; i++) {
        currentWindowSum += nums[i];
    }
    
    double maxWindowSum = currentWindowSum;
    
    for (int i = k; i < numsSize; i++) {
        
        currentWindowSum += nums[i] - nums[i - k];
        
        if (currentWindowSum > maxWindowSum) {
            maxWindowSum = currentWindowSum;
        }
    }
    
    return maxWindowSum / k;
}
