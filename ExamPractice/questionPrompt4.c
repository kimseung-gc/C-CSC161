#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NAME 50

struct student{
    char * name;
};

int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <file input>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char temp[MAX_NAME+1];
    FILE * stream = fopen(argv[1], "r");
    if(stream == NULL){
        fprintf(stderr, "Error in opening the file!\n");
    }
    int numSt = 0;
    int i = 0;
    if(fscanf(stream, "%d", &numSt) != 1){
        fprintf(stderr, "Invalid structure\n");
        return EXIT_FAILURE;
    }
    struct student * stuL = (struct student *)malloc(numSt * sizeof(struct student));
    while(fgets(temp, MAX_NAME, stream)!=NULL){
        stuL[i].name = (char *)malloc((strlen(temp)+1)*sizeof(char));
        strcpy(stuL[i].name, temp);
        i++;
    }
    srand(time(0));
    int randNum = rand()%numSt;
    printf("%s got chosen!\n", stuL[randNum].name);
    if(fclose(stream)){
        fprintf(stderr, "File not closed properly\n");
    }
    return EXIT_SUCCESS;
}