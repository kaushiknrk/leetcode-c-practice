#include <stdio.h>
#include <string.h>

char* smallestSubsequence(char *s) {

    static char result[1001];

    int last[26];
    int visited[26] = {0};
    char stack[1001];
    int top = -1;

    int n = strlen(s);

    for(int i = 0; i < n; i++)
    {
        last[s[i] - 'a'] = i;
    }

    for(int i = 0; i < n; i++)
    {
        char ch = s[i];

        if(visited[ch - 'a'])
            continue;

        while(top >= 0 &&
              stack[top] > ch &&
              last[stack[top] - 'a'] > i)
        {
            visited[stack[top] - 'a'] = 0;
            top--;
        }

        stack[++top] = ch;
        visited[ch - 'a'] = 1;
    }

    for(int i = 0; i <= top; i++)
        result[i] = stack[i];

    result[top + 1] = '\0';

    return result;
}
