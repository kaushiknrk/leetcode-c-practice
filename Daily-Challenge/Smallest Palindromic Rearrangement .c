#include <stdio.h>#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Forward declaration ensures the compiler recognizes the lowercase name
char* smallestPalindrome(char* s);

char* smallestPalindrome(char* s) {
    int len = strlen(s);
    int count[26] = {0};
    
    for (int i = 0; i < len; i++) {
        count[s[i] - 'a']++;
    }
    
    char* result = (char*)malloc((len + 1) * sizeof(char));
    result[len] = '\0';
    
    int left = 0;
    int right = len - 1;
    int odd_letter = -1;
    
    for (int i = 0; i < 26; i++) {
        if (count[i] % 2 != 0) {
            odd_letter = i;
        }
        
        int pairs = count[i] / 2;
        for (int j = 0; j < pairs; j++) {
            result[left] = 'a' + i;
            result[right] = 'a' + i;
            left++;
            right--;
        }
    }
    
    if (odd_letter != -1) {
        result[left] = 'a' + odd_letter;
    }
    
    return result;
}

#include <string.h>
#include <stdlib.h>

char* smallestPalindrome(char* s);

char* smallestPalindrome(char* s) {
    int len = strlen(s);
    int count[26] = {0};
    
    for (int i = 0; i < len; i++) {
        count[s[i] - 'a']++;
    }
    
    char* result = (char*)malloc((len + 1) * sizeof(char));
    result[len] = '\0';
    
    int left = 0;
    int right = len - 1;
    int odd_letter = -1;
    
    for (int i = 0; i < 26; i++) {
        if (count[i] % 2 != 0) {
            odd_letter = i;
        }
        
        int pairs = count[i] / 2;
        for (int j = 0; j < pairs; j++) {
            result[left] = 'a' + i;
            result[right] = 'a' + i;
            left++;
            right--;
        }
    }
    
    if (odd_letter != -1) {
        result[left] = 'a' + odd_letter;
    }
    
    return result;
}
