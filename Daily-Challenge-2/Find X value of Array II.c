#include <stdlib.h>
#include <string.h>

typedef struct {
    int count[5];
    int total_prod;
} SegmentNode;

SegmentNode* tree;
int K_val;

void merge_nodes(SegmentNode* res, SegmentNode* left, SegmentNode* right) {
    res->total_prod = (left->total_prod * right->total_prod) % K_val;
    memset(res->count, 0, sizeof(res->count));
    
    for (int i = 0; i < K_val; i++) {
        res->count[i] += left->count[i];
    }
    
    for (int j = 0; j < K_val; j++) {
        int target_rem = (left->total_prod * j) % K_val;
        res->count[target_rem] += right->count[j];
    }
}

void build_tree(int node, int start, int end, int* nums) {
    if (start == end) {
        int rem = nums[start] % K_val;
        memset(tree[node].count, 0, sizeof(tree[node].count));
        tree[node].count[rem] = 1;
        tree[node].total_prod = rem;
        return;
    }
    int mid = start + (end - start) / 2;
    build_tree(2 * node, start, mid, nums);
    build_tree(2 * node + 1, mid + 1, end, nums);
    merge_nodes(&tree[node], &tree[2 * node], &tree[2 * node + 1]);
}

void update_tree(int node, int start, int end, int idx, int val) {
    if (start == end) {
        int rem = val % K_val;
        memset(tree[node].count, 0, sizeof(tree[node].count));
        tree[node].count[rem] = 1;
        tree[node].total_prod = rem;
        return;
    }
    int mid = start + (end - start) / 2;
    if (idx <= mid) {
        update_tree(2 * node, start, mid, idx, val);
    } else {
        update_tree(2 * node + 1, mid + 1, end, idx, val);
    }
    merge_nodes(&tree[node], &tree[2 * node], &tree[2 * node + 1]);
}

SegmentNode query_tree(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = start + (end - start) / 2;
    if (r <= mid) {
        return query_tree(2 * node, start, mid, l, r);
    }
    if (l > mid) {
        return query_tree(2 * node + 1, mid + 1, end, l, r);
    }
    SegmentNode left_ans = query_tree(2 * node, start, mid, l, mid);
    SegmentNode right_ans = query_tree(2 * node + 1, mid + 1, end, mid + 1, r);
    SegmentNode res;
    merge_nodes(&res, &left_ans, &right_ans);
    return res;
}

int* resultArray(int* nums, int numsSize, int k, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    K_val = k;
    int tree_size = 4 * numsSize;
    tree = (SegmentNode*)malloc(tree_size * sizeof(SegmentNode));
    
    build_tree(1, 0, numsSize - 1, nums);
    
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    for (int i = 0; i < queriesSize; i++) {
        int index = queries[i][0];
        int value = queries[i][1];
        int start = queries[i][2];
        int xi = queries[i][3];
        
        update_tree(1, 0, numsSize - 1, index, value);
        
        SegmentNode ans_node = query_tree(1, 0, numsSize - 1, start, numsSize - 1);
        result[i] = ans_node.count[xi];
    }
    
    free(tree);
    return result;
}
