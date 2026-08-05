#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void dfs(int node, int** adj, int* adj_sizes, bool* is_suspicious) {
    is_suspicious[node] = true;
    for (int i = 0; i < adj_sizes[node]; i++) {
        int neighbor = adj[node][i];
        if (!is_suspicious[neighbor]) {
            dfs(neighbor, adj, adj_sizes, is_suspicious);
        }
    }
}

int* remainingMethods(int n, int k, int** invocations, int invocationsSize, int* invocationsColSize, int* returnSize) {
    int* adj_sizes = (int*)calloc(n, sizeof(int));
    int* adj_capacities = (int*)calloc(n, sizeof(int));
    int** adj = (int**)malloc(n * sizeof(int*));
    
    for (int i = 0; i < n; i++) {
        adj_capacities[i] = 2; 
        adj[i] = (int*)malloc(adj_capacities[i] * sizeof(int));
    }

    for (int i = 0; i < invocationsSize; i++) {
        int u = invocations[i][0];
        int v = invocations[i][1];
        
        if (adj_sizes[u] >= adj_capacities[u]) {
            adj_capacities[u] *= 2;
            adj[u] = (int*)realloc(adj[u], adj_capacities[u] * sizeof(int));
        }
        adj[u][adj_sizes[u]++] = v;
    }

    bool* is_suspicious = (bool*)calloc(n, sizeof(bool));
    dfs(k, adj, adj_sizes, is_suspicious);

    bool can_remove = true;
    for (int i = 0; i < invocationsSize; i++) {
        int u = invocations[i][0];
        int v = invocations[i][1];
        
        if (!is_suspicious[u] && is_suspicious[v]) {
            can_remove = false;
            break;
        }
    }

    int* result = (int*)malloc(n * sizeof(int));
    int count = 0;

    if (can_remove) {
        for (int i = 0; i < n; i++) {
            if (!is_suspicious[i]) {
                result[count++] = i;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            result[count++] = i;
        }
    }

    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adj_sizes);
    free(adj_capacities);
    free(is_suspicious);

    *returnSize = count;
    return result;
}
