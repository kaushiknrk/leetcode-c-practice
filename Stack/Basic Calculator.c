#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int calculate(char* s) {
    int len = strlen(s);
    
    int* stack = (int*)malloc(len * sizeof(int));
    int top = -1;
    
    int sum = 0;
    int sign = 1; 
    
    for (int i = 0; i < len; i++) {
        char ch = s[i];
        
        if (isdigit(ch)) {
            long long number = 0;
            while (i < len && isdigit(s[i])) {
                number = number * 10 + (s[i] - '0');
                i++;
            }
            i--; 
            sum += sign * number;
            
        } else if (ch == '+') {
            sign = 1;
            
        } else if (ch == '-') {
            sign = -1;
            
        } else if (ch == '(') {
            stack[++top] = sum;
            stack[++top] = sign;
            
            sum = 0;
            sign = 1;
            
        } else if (ch == ')') {
            int externalSign = stack[top--];
            int externalSum = stack[top--];
            
            sum = externalSum + externalSign * sum;
        }
    }
    
    free(stack);
    return sum;
}
