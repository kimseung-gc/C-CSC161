#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef __floatStack_h__
#define __floatStack_h__

#define MAX_STRING_LENGTH 3000
#define MAX_NAME_LENGTH 50

typedef struct node {
  double data;
  struct node * next;
} stackNode;

typedef struct {
  unsigned int size;
  char name[MAX_NAME_LENGTH+1];
  stackNode * top;
} floatStack;

bool
isEmptyFloat (const floatStack * stack) {
  return (stack->size == 0);
}

bool
isFullFloat () {
  /* determine whether there are no available positions in a stackArray */
  stackNode * temp = (stackNode *)malloc(sizeof(stackNode));
  bool temp1 = (temp == NULL);
  free(temp);
  return temp1;
} // isFull

void
initializeFloat (floatStack * stack, char * name){
  stack->top = NULL;
  stack->size = 0;
  strncpy(stack->name,name,MAX_NAME_LENGTH);
}

bool
push (floatStack * stack, double item) {
  /* return false if stack full */
  stackNode * temp = (stackNode *)malloc(sizeof(stackNode));
  if(temp == NULL){
    printf("Unable to allocate memory \n");
    return false;
  }
  temp->data = item;
  if (isEmptyFloat(stack))
    stack->top = temp;
  else if(isFullFloat()){
    printf("The stack is full! \n");
  }
  else{
    temp -> next = stack->top;
    stack->top = temp;
  }
  /* add item to stack */
  (stack->size) ++;
  return true;
} // push

void
printFloat (const floatStack * stack){
  printf("Current elements in the stack %s:\n", stack->name);
  for(stackNode * current = stack->top; current != NULL; current = current->next){
    printf("%lf ", current->data);
  }
  printf("\n");
}

void
clearFloat(floatStack * stack){
  if(isEmptyFloat(stack)){
    return;
  }
  for(stackNode * current = stack->top; current != NULL; current = stack->top){
    //printf("HG");
    stackNode * temp = stack->top->next;
    free(stack->top);
    stack->top = temp;
  }
  stack->top = NULL;
}

#endif
