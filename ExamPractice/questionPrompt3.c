#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct box{
    double length;
    double width;
    double height;
    double volume;
    bool passes;
};

int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf(stderr, "Error! Usage: %s <file input> <file output>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE * stream = fopen(argv[1], "r");
    if(stream == NULL){
        fprintf(stderr, "Error in opening the file!\n");
        return EXIT_FAILURE;
    }
    int n = 0;
    int inp = fscanf(stream, "%d", &n);
    if(inp == -1 || inp == 0){
        fprintf(stderr, "Invalid input! Check the structure of the txt file!\n");
        return EXIT_FAILURE;
    }
    struct box * boxArr = (struct box *)malloc(n*sizeof(struct box));
    int i = 0;
    double length, width, height;
    while((fscanf(stream, "%lf %lf %lf", &length, &width, &height) != -1) && (i<n)){
        boxArr[i].height = height;
        boxArr[i].width = width;
        boxArr[i].length = length;
        boxArr[i].volume = length*width*height;
        if(height < 41.0){
            printf("%lf\n", boxArr[i].volume);
            boxArr[i++].passes = true;
        }else{
            boxArr[i++].passes = false;
        }
    }
    return EXIT_SUCCESS;
}