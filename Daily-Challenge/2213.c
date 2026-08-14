#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int max_len;
    int pref_len;
    int suff_len;
    int total_len;
    char left_char;
    char right_char;
} Node;

Node tree[400005];

void merge(Node* parent, Node* left, Node* right) {
    parent->total_len = left->total_len + right->total_len;
    parent->left_char = left->left_char;
    parent->right_char = right->right_char;

    parent->pref_len = left->pref_len;
    if (left->pref_len == left->total_len && left->left_char == right->left_char) {
        parent->pref_len += right->pref_len;
    }

    parent->suff_len = right->suff_len;
    if (right->suff_len == right->total_len && right->right_char == left->right_char) {
        parent->suff_len += left->suff_len;
    }

    parent->max_len = MAX(left->max_len, right->max_len);
    if (left->right_char == right->left_char) {
        parent->max_len = MAX(parent->max_len, left->suff_len + right->pref_len);
    }
    parent->max_len = MAX(parent->max_len, MAX(parent->pref_len, parent->suff_len));
}

void build(int node, int start, int end, const char* s) {
    if (start == end) {
        tree[node].max_len = 1;
        tree[node].pref_len = 1;
        tree[node].suff_len = 1;
        tree[node].total_len = 1;
        tree[node].left_char = s[start];
        tree[node].right_char = s[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid, s);
    build(2 * node + 1, mid + 1, end, s);
    merge(&tree[node], &tree[2 * node], &tree[2 * node + 1]);
}

void update(int node, int start, int end, int idx, char val) {
    if (start == end) {
        tree[node].left_char = val;
        tree[node].right_char = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) {
        update(2 * node, start, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, end, idx, val);
    }
    merge(&tree[node], &tree[2 * node], &tree[2 * node + 1]);
}

int* longestRepeating(char* s, char* queryCharacters, int* queryIndices, int queryIndicesSize, int* returnSize) {
    int n = strlen(s);
    build(1, 0, n - 1, s);

    int* result = (int*)malloc(queryIndicesSize * sizeof(int));
    *returnSize = queryIndicesSize;

    for (int i = 0; i < queryIndicesSize; i++) {
        update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
        result[i] = tree[1].max_len;
    }

    return result;
}
