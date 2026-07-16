#include <stdlib.h>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

long long gcdSum(int *nums, int n)
{
    int prefixGcd[n];

    int maxSoFar = nums[0];

    for (int i = 0; i < n; i++)
    {
        if (nums[i] > maxSoFar)
        {
            maxSoFar = nums[i];
        }

        prefixGcd[i] = gcd(nums[i], maxSoFar);
    }

    qsort(prefixGcd, n, sizeof(int), compare);

    int left = 0;
    int right = n - 1;

    long long answer = 0;

    while (left < right)
    {
        answer += gcd(prefixGcd[left], prefixGcd[right]);

        left++;
        right--;
    }

    return answer;
}
