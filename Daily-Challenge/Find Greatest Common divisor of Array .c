#include <stdio.h>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int findGCD(int* nums, int numsSize)
{
    int min = nums[0];
    int max = nums[0];

    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i] < min)
            min = nums[i];

        if (nums[i] > max)
            max = nums[i];
    }

    return gcd(min, max);
}
