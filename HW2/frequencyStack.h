#include <stdio.h>
#include <stdbool.h>
#include "floatStack.h"

#ifndef __frequencyStack_h__
#define __frequencyStack_h__

typedef struct freqStackNode freqStackNode_t;

struct freqStackNode
{
  int data;
  int frequency;
  freqStackNode_t * next;
};

typedef struct {
  unsigned int size;
  unsigned int length;
  freqStackNode_t * top;
} freqStack;

bool
isEmptyFreq (const freqStack * stack) {
  return (stack->length == 0);
}

void
initializeFreq(freqStack * stack){
    freqStackNode_t * temp = (freqStackNode_t *)malloc(sizeof(freqStackNode_t));
    if(temp == NULL){
      printf("Unable to allocate memory\n");
      return;
    }
    temp->data = -1.0;
    temp->frequency = 0;
    temp->next = NULL;
    stack->size = 0;
    stack->top = temp;
    stack->length = 0;
}

void
addFreq (freqStack * stack, double dt) {
  freqStackNode_t * firstStack = stack->top;
  int intdt = (int) dt;
  if (firstStack->data==-1.0){
    firstStack->data = intdt;
    firstStack->frequency++;
    stack->length++;
  }else{
    freqStackNode_t * lastElement;
    for(freqStackNode_t * current = firstStack; current != NULL; current = current->next){
        if(current->data == intdt){
            stack->size++;
            current->frequency++;
            return;
        }
    }
    freqStackNode_t * temp = (freqStackNode_t *)malloc(sizeof(freqStackNode_t));
    if(temp == NULL){
        printf("Unable to allocate memory \n");
        return;
    }
    temp->frequency=0;
    freqStackNode_t * prev;
    freqStackNode_t * nthInd;
    bool f = true;
    /* sorting algorithm ahead. This is done while counting the frequency in order to make
       the function more efficient. Keeping the stack sorted makes the data analysis process
       easier.*/
    for(freqStackNode_t * current = firstStack; current != NULL && f == true; current = current->next){
        if(current->next == NULL){
          if(current->data < intdt){
            nthInd = current;
            prev = NULL;
            f = false;
          }else{
            prev = current;
            nthInd = NULL;
            f = false;
          }
        } else if(current->data > intdt && intdt > (current->next)->data){
          prev = current;
          nthInd = current->next;//biggest to smallest
          f = false;
        }
    }
    temp->data = intdt;
    temp->frequency++;
    if(prev == NULL){
      temp->next = nthInd;
      stack->top = temp;
    }else{
      prev->next = temp;
      temp->next = nthInd;
    }
    stack->length++;
  }
  stack->size++;
  return;
} // push while keeping the list sorted from biggest to smallest.

freqStack
countFreq(const floatStack * stack){
  freqStack freqS;
  initializeFreq(&freqS);
  for(stackNode * current = stack->top; current != NULL; current = current->next){
    addFreq(&freqS, current->data);
  }
  return freqS;
}

void
printFreq (freqStack * stack){
  if(isEmptyFreq(stack)){
    printf("The stack is empty!!\n");
    return;
  }
  freqStackNode_t * firstStack = stack->top;
  printf("Current elements in the stack:\n");
  for(freqStackNode_t * current = firstStack; current != NULL; current = current->next){
    printf("%d %d\n", current->data, current->frequency);
  }
  printf("\n");
}

void
clearFreq(freqStack * stack){
  if(isEmptyFreq(stack)){
    return ;
  }
  for(freqStackNode_t * current = stack->top; current != NULL; current = stack->top){
    freqStackNode_t * temp = current->next;
    free(current);
    stack->top = temp;
  }
  stack->top = NULL;
}

#endif