bool checkDivisibility(int n) {
    int original_num = n;
    int digit_sum = 0;
    int digit_product = 1; 
    while (n > 0) {
        int digit = n % 10;
        
        digit_sum += digit;
        digit_product *= digit;
        
        n = n / 10;
    }

    int total_divisor = digit_sum + digit_product;

    if (total_divisor == 0) {
        return false;
    }

    return (original_num % total_divisor == 0);
}
