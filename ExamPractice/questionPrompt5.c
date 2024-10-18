#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAX_NAME 300

typedef struct{
    char name[MAX_NAME+1];
    bool marked;
} student;

int main(int argc, char * argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: %s <file input> <file output>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE * stream1 = fopen(argv[1], "r");
    FILE * stream2 = fopen(argv[2], "w");
    if(stream1 == NULL || stream2 == NULL){
        fprintf(stderr, "File not properly opened!\n");
        return EXIT_FAILURE;
    }
    int numSt = 0;
    if(fscanf(stream1, "%d\n", &numSt) != 1){
        return EXIT_FAILURE;
    }
    student * stuL = (student *)malloc(numSt*sizeof(student));
    char temp[MAX_NAME+1];
    int i = 0;
    while(fgets(temp, MAX_NAME, stream1) != NULL){
        strcpy(stuL[i].name, temp);
        stuL[i].marked = false;
        i++;
    }
    srand(time(0));
    int teamSize = 0;
    while(teamSize != numSt/2){
        int randInd1 = 0;
        int randInd2 = 0;
        while(stuL[randInd1].marked){
            randInd1 = rand()%numSt;
        }
        while(stuL[randInd2].marked || randInd1 == randInd2){
            randInd2 = rand()%numSt;
        }
        fprintf(stream2, "team %d: %s | %s\n", teamSize+1, stuL[randInd1].name, stuL[randInd2].name);
        stuL[randInd1].marked = true; 
        stuL[randInd2].marked = true;
        teamSize++;
    }
    for(int j = 0; j<numSt; j++){
        if(!stuL[j].marked){
            fprintf(stream2, "%s is left alone\n", stuL[j].name);
        }
    }
    if(fclose(stream1)||fclose(stream2)){
        fprintf(stderr, "Unable to close file!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}