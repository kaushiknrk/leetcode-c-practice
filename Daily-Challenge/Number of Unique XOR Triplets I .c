int uniqueXorTriplets(int* nums, int numsSize) {
    if (numsSize == 1) {
        return 1;
    }
    if (numsSize == 2) {
        return 2;
    }
    
    int powerOfTwo = 1;
    while (powerOfTwo <= numsSize) {
        powerOfTwo <<= 1;
    }
    
    return powerOfTwo;
}
