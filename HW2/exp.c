#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node{
    int n;
    struct node * next;
} node_t;

void printLast(node_t * list){
    if(list == NULL){
        printf("List is empty!");
        return;
    }else if(list->next == NULL){
        printf("%d\n", list->n);
        return;
    }
    return printLast(list->next);
}

int main(){
    node_t * list = NULL;
    printLast(list);
    return 0;
}