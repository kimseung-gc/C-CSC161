#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef __stringFunctionsExtended_h__
#define __stringFunctionsExtended_h__

#include <string.h>
#include "floatStack.h"

char * reverseName(char * str){
    char * temp= (char *)malloc((MAX_NAME_LENGTH+1)*sizeof(char));
    int stl = strlen(str);
    if(stl == 0){
        return "";
    }
    int i  = 0;
    for(i = 0; i<stl; i++){
        temp[i] = str[stl-i-1];
    }
    temp[i] = '\0';
    return temp;
}

char * bringName(char * str){
    char temp[MAX_NAME_LENGTH+1];
    int stl = strlen(str);
    if(stl == 0){
        return "";
    }
    int i =0;
    for(i=0; i< stl; i++){
        if(str[stl-i] == '\"'){
            i = stl;
        }
        temp[i] = str[stl-i-1];
    }
    temp[i-1] = '\0';
    return reverseName(temp);
}

char * subString(char * str, int i, int j){
    if(i+j < MAX_STRING_LENGTH){
        char* temp = (char*)malloc((MAX_STRING_LENGTH+1)*sizeof(char));
        for(int k = 0; k<j; k++){
            temp[k] = str[i+k];
        }
        return temp;
    }else{
        return NULL;
    }
}

bool
isNumber(char * str, unsigned long i){
    if(i == strlen(str)-1){
        return (isdigit(str[i])||(str[i] == '.')||(str[i]=='-'));
    }
    return ((isdigit(str[i])||(str[i] == '.')||(str[i]=='-')) && isNumber(str, i+1));
}

floatStack stringSplitCPI(char * stringSentence, char * token){
    floatStack stackOfSplitElements;
    char temp[MAX_STRING_LENGTH+1];
    unsigned int j = 0;
    unsigned int splitCount = 0;
    if(strlen(stringSentence)<strlen(token)){
        printf("Invalid input file!\n");
        return stackOfSplitElements;
    }
    initializeFloat(&stackOfSplitElements, "Empty!");
    for(unsigned int i = 0; (i<strlen(stringSentence))&&(j<MAX_STRING_LENGTH+1); i++){
        temp[j] = stringSentence[i];
        j++;
        if(stringSentence[i] == token[0]){
            if(strcmp(subString(stringSentence, i, strlen(token)), token) == 0){
                splitCount++;
                temp[j-1] = '\0';
                if(strcmp(temp, "") != 0 && 3 < splitCount){
                    if(!isNumber(temp, 0)){
                        initializeFloat(&stackOfSplitElements, "Empty!");
                        printf("Some inputs not a number!!\n");
                        return stackOfSplitElements;
                    }else if(atof(temp)<0){
                        printf("Invalid CPI! (CPI has to be larger than 0).\n");
                        return stackOfSplitElements;
                    }else if(!push(&stackOfSplitElements,atof(temp))){
                        printf("Error in pushing!\n");
                        return stackOfSplitElements;
                    }
                }else if (splitCount==1){
                    initializeFloat(&stackOfSplitElements, bringName(temp));
                }
                j = 0;
                i+=strlen(token)-1;
            }
        }
        if(splitCount == 0 && i == strlen(stringSentence)-1){
            printf("Incorrect input file!\n");
            return stackOfSplitElements;
        }
    }
    if(isEmptyFloat(&stackOfSplitElements)){
        printf("Wrong splitter!\n");
        return stackOfSplitElements;
    }
    return stackOfSplitElements;
}

#endif