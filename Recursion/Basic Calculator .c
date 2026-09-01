int calculateHelper(char* s, int* index) {
    int total = 0;
    int current_number = 0;
    int sign = 1;

    while (s[*index] != '\0') {
        char c = s[*index];
        (*index)++;

        if (c >= '0' && c <= '9') {
            current_number = current_number * 10 + (c - '0');
        } 
        else if (c == '(') {
            current_number = calculateHelper(s, index);
        } 
        else if (c == '+' || c == '-') {
            total += sign * current_number;
            current_number = 0;
            sign = (c == '+') ? 1 : -1;
        } 
        else if (c == ')') {
            break;
        }
    }

    total += sign * current_number;
    return total;
}

int calculate(char* s) {
    int index = 0;
    return calculateHelper(s, &index);
}
