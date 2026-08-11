#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int min;
} StackNode;

typedef struct {
    StackNode* data;
    int top;
    int capacity;
} MinStack;

MinStack* minStackCreate() {
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    obj->capacity = 1000; 
    obj->data = (StackNode*)malloc(obj->capacity * sizeof(StackNode));
    obj->top = -1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    if (obj->top == obj->capacity - 1) {
        obj->capacity *= 2;
        obj->data = (StackNode*)realloc(obj->data, obj->capacity * sizeof(StackNode));
    }
    
    obj->top++;
    obj->data[obj->top].val = val;
    
    if (obj->top == 0) {
        obj->data[obj->top].min = val;
    } else {
        int previousMin = obj->data[obj->top - 1].min;
        obj->data[obj->top].min = (val < previousMin) ? val : previousMin;
    }
}

void minStackPop(MinStack* obj) {
    if (obj->top >= 0) {
        obj->top--;
    }
}

int minStackTop(MinStack* obj) {
    return obj->data[obj->top].val;
}

int minStackGetMin(MinStack* obj) {
    return obj->data[obj->top].min;
}

void minStackFree(MinStack* obj) {
    free(obj->data);
    free(obj);
}
