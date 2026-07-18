#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int cmpInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cmpLongLong(const void *a, const void *b) {
    long long x = ((long long *)a)[0];
    long long y = ((long long *)b)[0];

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int upperBound(long long *arr, int size, long long target) {
    int left = 0, right = size - 1;
    int ans = size;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] > target) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return ans;
}

int* gcdValues(int* nums, int numsSize, long long* queries,
               int queriesSize, int* returnSize) {

    int maxVal = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxVal)
            maxVal = nums[i];
    }

    int *freq = calloc(maxVal + 1, sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    long long *cnt = calloc(maxVal + 1, sizeof(long long));
    int *multiples = calloc(maxVal + 1, sizeof(int));

    for (int g = 1; g <= maxVal; g++) {
        long long total = 0;

        for (int multiple = g; multiple <= maxVal; multiple += g) {
            total += freq[multiple];
        }

        multiples[g] = (int)total;
    }

    for (int g = maxVal; g >= 1; g--) {
        long long total = multiples[g];

        cnt[g] = total * (total - 1) / 2;

        for (int multiple = 2 * g; multiple <= maxVal; multiple += g) {
            cnt[g] -= cnt[multiple];
        }
    }

    long long *prefix = calloc(maxVal + 1, sizeof(long long));

    for (int g = 1; g <= maxVal; g++) {
        prefix[g] = prefix[g - 1] + cnt[g];
    }

    int *answer = malloc(sizeof(int) * queriesSize);

    for (int i = 0; i < queriesSize; i++) {
        long long target = queries[i] + 1;

        int left = 1;
        int right = maxVal;
        int res = maxVal;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (prefix[mid] >= target) {
                res = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        answer[i] = res;
    }

    free(freq);
    free(cnt);
    free(multiples);
    free(prefix);

    *returnSize = queriesSize;
    return answer;
}
