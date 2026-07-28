#include <stdlib.h>
#include <stdbool.h>

#define HASH_SIZE 100003

typedef struct Node {
    int remainder;
    int index;
    struct Node* next;
} Node;

bool checkSubarraySum(int* nums, int numsSize, int k) {
    Node* table[HASH_SIZE] = {NULL};
    
    Node* base_node = (Node*)malloc(sizeof(Node));
    base_node->remainder = 0;
    base_node->index = -1;
    base_node->next = NULL;
    table[0] = base_node;

    int running_sum = 0;

    for (int i = 0; i < numsSize; i++) {
        running_sum += nums[i];
        int rem = running_sum % k;
        if (rem < 0) {
            rem += k;
        }

        unsigned int h = (unsigned int)rem % HASH_SIZE;
        Node* curr = table[h];
        bool found = false;

        while (curr) {
            if (curr->remainder == rem) {
                if (i - curr->index >= 2) {
                    for (int m = 0; m < HASH_SIZE; m++) {
                        Node* tmp = table[m];
                        while (tmp) {
                            Node* to_free = tmp;
                            tmp = tmp->next;
                            free(to_free);
                        }
                    }
                    return true;
                }
                found = true;
                break;
            }
            curr = curr->next;
        }

        if (!found) {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->remainder = rem;
            new_node->index = i;
            new_node->next = table[h];
            table[h] = new_node;
        }
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = table[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }

    return false;
}
