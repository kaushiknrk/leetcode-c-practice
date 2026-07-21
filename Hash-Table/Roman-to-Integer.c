// Helper function to return the integer value of a Roman character
int getRomanValue(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default:  return 0;
    }
}

int romanToInt(char* s) {
    int total = 0;
    int length = strlen(s);

    // Loop through the string up to the second-to-last character
    for (int i = 0; i < length - 1; i++) {
        // Compare current character value with the next character value
        if (getRomanValue(s[i]) < getRomanValue(s[i + 1])) {
            total -= getRomanValue(s[i]);
        } else {
            total += getRomanValue(s[i]);
        }
    }

    // Always add the value of the very last character
    total += getRomanValue(s[length - 1]);

    return total;
}
