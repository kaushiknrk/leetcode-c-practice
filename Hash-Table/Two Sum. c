#include <stdlib.h>

struct HashTable {
    int key;
    int value;
    struct HashTable* next;
};

void insert(struct HashTable** table, int size, int key, int value) {
    int index = abs(key) % size;
    struct HashTable* newNode = malloc(sizeof(struct HashTable));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table[index];
    table[index] = newNode;
}

struct HashTable* search(struct HashTable** table, int size, int key) {
    int index = abs(key) % size;
    struct HashTable* curr = table[index];
    while (curr != NULL) {
        if (curr->key == key) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int hashSize = numsSize * 2;
    struct HashTable** table = calloc(hashSize, sizeof(struct HashTable*));
    int* result = malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        struct HashTable* found = search(table, hashSize, complement);
        
        if (found != NULL) {
            result[0] = found->value;
            result[1] = i;
            
            for (int j = 0; j < hashSize; j++) {
                struct HashTable* curr = table[j];
                while (curr != NULL) {
                    struct HashTable* tmp = curr;
                    curr = curr->next;
                    free(tmp);
                }
            }
            free(table);
            return result;
        }
        insert(table, hashSize, nums[i], i);
    }

    free(table);
    *returnSize = 0;
    return NULL;
}
