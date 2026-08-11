#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int evalRPN(char** tokens, int tokensSize) {
    int* stack = (int*)malloc(tokensSize * sizeof(int));
    int top = -1;

    for (int i = 0; i < tokensSize; i++) {
        char* token = tokens[i];

        if ((token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') && token[1] == '\0') {
            int b = stack[top--];
            int a = stack[top--];

            if (token[0] == '+') {
                stack[++top] = a + b;
            } else if (token[0] == '-') {
                stack[++top] = a - b;
            } else if (token[0] == '*') {
                stack[++top] = a * b;
            } else if (token[0] == '/') {
                stack[++top] = a / b;
            }
        } else {
            stack[++top] = atoi(token);
        }
    }

    int result = stack[0];
    
    free(stack);    
    return result;
}
