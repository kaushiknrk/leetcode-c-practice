#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

typedef struct {
    int start;
    int end;
} Block;

int** createSparseTable(int* arr, int n, int* num_cols) {
    if (n == 0) {
        *num_cols = 0;
        return NULL;
    }
    int k = 0;
    while ((1 << (k + 1)) <= n) {
        k++;
    }
    k += 1;
    *num_cols = k;
    
    int** st = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        st[i] = (int*)malloc(k * sizeof(int));
        st[i][0] = arr[i];
    }
    
    for (int j = 1; j < k; j++) {
        for (int i = 0; i <= n - (1 << j); i++) {
            st[i][j] = MAX(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }
    return st;
}

int querySparseTable(int** st, int l, int r) {
    if (l > r) return -1e9;
    int len = r - l + 1;
    int j = 0;
    while ((1 << (j + 1)) <= len) {
        j++;
    }
    return MAX(st[l][j], st[r - (1 << j) + 1][j]);
}

int findFirst(Block* blocks, int m, int target_start) {
    int l = 0, r = m - 1, ans = m;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (blocks[mid].start >= target_start) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int findLast(Block* blocks, int m, int target_end) {
    int l = 0, r = m - 1, ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (blocks[mid].end <= target_end) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int* maxActiveSectionsAfterTrade(char* s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int n = strlen(s);
    int total_ones = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') total_ones++;
    }
    
    Block* blocks = (Block*)malloc(n * sizeof(Block));
    int m = 0;
    int in_block = 0;
    int start = -1;
    
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            if (!in_block) {
                start = i;
                in_block = 1;
            }
        } else {
            if (in_block) {
                blocks[m].start = start;
                blocks[m].end = i - 1;
                m++;
                in_block = 0;
            }
        }
    }
    if (in_block) {
        blocks[m].start = start;
        blocks[m].end = n - 1;
        m++;
    }
    
    int* ans = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    if (m == 0) {
        for (int i = 0; i < queriesSize; i++) {
            ans[i] = total_ones;
        }
        free(blocks);
        return ans;
    }
    
    int* static_val = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        int b_start = blocks[i].start;
        int b_end = blocks[i].end;
        int prev_B_end = (i > 0) ? blocks[i-1].end : -1;
        int next_B_start = (i < m - 1) ? blocks[i+1].start : n;
        static_val[i] = total_ones - (b_end - b_start + 1) + next_B_start - prev_B_end - 1;
    }
    
    int num_cols = 0;
    int** st = createSparseTable(static_val, m, &num_cols);
    
    for (int q = 0; q < queriesSize; q++) {
        int l = queries[q][0];
        int r = queries[q][1];
        
        int idx_first = findFirst(blocks, m, l + 1);
        int idx_last = findLast(blocks, m, r - 1);
        
        if (idx_first > idx_last) {
            ans[q] = total_ones;
            continue;
        }
        
        int res = total_ones;
        
        int b_start_f = blocks[idx_first].start;
        int b_end_f = blocks[idx_first].end;
        int prev_B_end_f = (idx_first > 0) ? blocks[idx_first-1].end : -1;
        int next_B_start_f = (idx_first < m - 1) ? blocks[idx_first+1].start : n;
        int left_bound_f = MAX(l, prev_B_end_f + 1);
        int right_bound_f = MIN(r, next_B_start_f - 1);
        int val_first = total_ones - (b_end_f - b_start_f + 1) + (right_bound_f - left_bound_f + 1);
        res = MAX(res, val_first);
        
        if (idx_first != idx_last) {
            int b_start_l = blocks[idx_last].start;
            int b_end_l = blocks[idx_last].end;
            int prev_B_end_l = (idx_last > 0) ? blocks[idx_last-1].end : -1;
            int next_B_start_l = (idx_last < m - 1) ? blocks[idx_last+1].start : n;
            int left_bound_l = MAX(l, prev_B_end_l + 1);
            int right_bound_l = MIN(r, next_B_start_l - 1);
            int val_last = total_ones - (b_end_l - b_start_l + 1) + (right_bound_l - left_bound_l + 1);
            res = MAX(res, val_last);
            
            if (idx_first + 1 <= idx_last - 1) {
                int middle_max = querySparseTable(st, idx_first + 1, idx_last - 1);
                res = MAX(res, middle_max);
            }
        }
        
        ans[q] = res;
    }
    
    for (int i = 0; i < m; i++) {
        free(st[i]);
    }
    free(st);
    free(static_val);
    free(blocks);
    
    return ans;
}
