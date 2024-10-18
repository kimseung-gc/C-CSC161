#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char * argv[]){
    if(argc != 3){
        fprintf (stderr, "Usage: %s file-input file-output\n",argv[0]);
        return EXIT_FAILURE;
    }
    FILE * stream1 = fopen(argv[1], "r");
    FILE * stream2 = fopen(argv[2], "w");
    if(stream1 == NULL || stream2 == NULL){
        fprintf (stderr, "Error in opening the file(s)\n");
        return EXIT_FAILURE;
    }
    char ch;
    while((ch = fgetc(stream1)) != EOF){
        fprintf(stream2, "%c", ch);
    }
    if(fclose(stream1)||fclose(stream2)){
        fprintf (stderr, "Error in closing the file(s)\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}