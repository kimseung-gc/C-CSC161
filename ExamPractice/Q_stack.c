#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct binarySt
{
    bool digit;
    struct binarySt * next;
};

struct Stack {
    unsigned int dodecNum;
    struct binarySt * first;
};

void
initialize(struct Stack * st){
    printf("Input a number in base 10: ");
    unsigned int temp = 0;
    scanf("%u", &temp);
    st->dodecNum = temp;
    st->first = NULL;
}

bool
isEmpty(struct Stack * st){
    return (st->first == NULL);
}

bool
isFull(){
    struct binarySt * temp = (struct binarySt *)malloc(sizeof(struct binarySt));
    bool ret = (temp == NULL);
    free(temp);
    return ret;
}

bool
push(struct Stack * st, bool item){
    struct binarySt * temp = (struct binarySt *)malloc(sizeof(struct binarySt));
    if(temp==NULL || isFull()){
        return false;
    }
    temp->digit = item;
    temp->next = st->first;
    st->first = temp;
    return true;
}

int
pop(struct Stack * st){
    if(isEmpty(st)){
        return -1;
    }
    bool temp = (st->first)->digit;
    struct binarySt * temp1 = (st->first)->next;
    free(st->first);
    st->first = temp1;
    return temp;
}

void clearSt(struct Stack * st){
    if(isEmpty(st)){
        return;
    }
    while(pop(st) != -1){
        ;
    }
}

void convertToBase2(struct Stack * st){
    int nxt = st->dodecNum;
    if(isFull()){
        clearSt(st);
    }
    if(nxt == 0){
        push(st, 0);
    }
    while(nxt != 0){
        push(st, nxt%2);
        nxt/=2;
    }
}

void printBase2(struct Stack * st){
    if(isEmpty(st)){
        printf("The stack is empty!\n");
        return;
    }
    int dig;
    while((dig = pop(st)) != -1){
        printf("%d",dig);
    }
    printf("\n");
}

int main(){
    struct Stack stack;
    initialize(&stack);
    convertToBase2(&stack);
    printBase2(&stack);
    return 0;
}