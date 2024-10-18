#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "floatStack.h"
#include "frequencyStack.h"
#include "stringFunctionsExtended.h"
#ifndef __dataAnalysis_h__
#define __dataAnalysis_h__
#define DIVIDER " "

typedef struct dataStack dataStack_t;

struct dataStack
{
  char name[MAX_NAME_LENGTH+1];
  double stdDeviation;
  double mean;
  int mode;
  int min;
  int Q1;
  int median;
  int Q3;
  int max;
  dataStack_t * next;
};

void
printingBufferSizeKRforData(char * item, int bufferMAX){
    int temp = strlen(item)/3;
    for(int i = 0; i<bufferMAX-temp; i++){
        printf(" ");
    }
}

void
printData(dataStack_t * stack){
    if(stack == NULL){
        printf("Empty stack!\n");
        return;
    }
    printf("Region                        Standard Dev  Average         Mode       Min         Q1         Median     Q3         Max\n");
    for(dataStack_t * current = stack; current != NULL; current = current->next){
        printf("%-30s", current->name);
        //printingBufferSizeKRforData(current->name, 10);
        printf("%-14lf", current->stdDeviation);
        printf("%-16lf", current->mean);
        printf("%-11d", current->mode);
        printf("%-11d ", current->min);
        printf("%-11d", current->Q1);
        printf("%-11d", current->median);
        printf("%-11d", current->Q3);
        printf("%-11d", current->max);
        printf("\n");
    }
}

int
findMode(freqStack * stack){
    freqStackNode_t * first = stack->top;
    if(first == NULL){
        return -1;
    }
    int mode = first->data;
    int maxFreq = first->frequency;
    for(freqStackNode_t * current = first->next; current != NULL; current = current->next){
        if(current->frequency > maxFreq){
            maxFreq = current->frequency;
            mode = current->data;
        }
    }
    return mode;
}

double 
average(floatStack * stack){
    if(isEmptyFloat(stack)){
        return -1.0;
    }
    double sum = 0.0;
    for(stackNode * current = (stack->top); current != NULL; current = current->next){
        sum += current->data;
    }
    sum /= (double)stack->size;
    return sum;
}

double 
stdDevHelper(stackNode * node, double avg){
    if(node == NULL){
        return 0.0;
    }
    double x = node->data;
    double temp = x-avg;
    return pow(temp, 2.0) + stdDevHelper(node->next, avg);
}

double 
stdDev(floatStack * stack){
    double avg = average(stack);
    int n = stack->size;
    double temp = (stdDevHelper(stack->top, avg))/(n-1);
    return pow(temp, 0.5);;
}

void
findQ1Q2Q3(freqStack * sortedStack, dataStack_t * dest){
    freqStackNode_t * first = sortedStack->top;
    if(first == NULL){
        return ;
    }
    int Q3Ind = sortedStack->size/4;// This is Q3 as the list is ordered from biggest to the smallest. Thus, reverse logic.
    int Q2Ind = sortedStack->size/3;
    int Q1Ind = (int)(((double)sortedStack->size)*0.75);// This is Q1 as the list is ordered from biggest to the smallest. Thus, reverse logic.
    int QCount = 0;
    int prevC = 0;
    for(freqStackNode_t * current = first; current != NULL; current = current->next){
        prevC = QCount;
        QCount += current->frequency;
        if(QCount >= Q1Ind && prevC < Q1Ind){
          dest->Q1 = current->data;
        }
        if(QCount >= Q2Ind && prevC < Q2Ind){
          dest->median = current->data;
        }
        if(QCount >= Q3Ind && prevC < Q3Ind){
          dest->Q3 = current->data;
        }
    }
}

void
makeNewData(dataStack_t ** stack, floatStack * flSt){
    if(flSt == NULL){
        return;
    }
    dataStack_t * newSt = (dataStack_t *)malloc(sizeof(dataStack_t));
    if(newSt == NULL){
        printf("Error in allocating memory \n");
        return;
    }
    newSt->next = NULL;
    strcpy(newSt->name, flSt->name);
    newSt->mean = average(flSt);
    newSt->stdDeviation = stdDev(flSt);
    freqStack temp = countFreq(flSt);
    clearFloat(flSt);
    for(freqStackNode_t * current = temp.top; current != NULL; current= current->next){
        if(current->next == NULL){
            newSt->min = current->data;
        }
    }
    newSt->max = (temp.top)->data;
    findQ1Q2Q3(&temp, newSt);
    newSt->mode = findMode(&temp);
    clearFreq(&temp);
    if(*stack == NULL){
        *stack = newSt;
        return;
    }
    dataStack_t * lastOne;
    for(dataStack_t * current = *stack; current != NULL; current = current->next){
        if(current->next == NULL){
            lastOne = current;
        }
    }
    lastOne->next = newSt;
}

#endif