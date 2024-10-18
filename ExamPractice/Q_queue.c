#include <stdio.h>
#include <stdbool.h>

struct
node{
    int n;
    struct node * next;
};

struct 
queue{
    struct node * first;
    struct node * last;
};

void
initialize(struct queue * Queue){
    Queue->first = NULL;
    Queue->last = NULL;
}

bool
isEmpty(struct queue * Queue){
    return ((Queue->first == NULL) && (Queue->last == NULL));
}

bool
isFull(){
    struct node * temp = (struct node *)malloc(sizeof(struct node));
    bool ret = (temp == NULL);
    free(temp);
    return ret;
}

bool
enqueue(struct queue * Queue, int n){
    if(isFull()){
        fprintf(stderr, "The queue is full\n");
        return false;
    }
    struct node * temp = (struct node *)malloc(sizeof(struct node));
    if(temp == NULL){
        fprintf(stderr, "Error in allocating memory\n");
        return false;
    }
    temp->n = n;
    temp->next = NULL;
    if(isEmpty(Queue)){
        Queue->first = temp;
        Queue->last = temp;
        return true;
    }
    (Queue->last)->next = temp;
    Queue->last = temp;
    return true;
}
