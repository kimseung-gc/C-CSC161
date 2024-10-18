#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum drinks {black_coffee, black_tea, green_tea, white_tea, iced_tea, coke};

int main(int argc, char * argv[]){
    double totalCaff = 0;
    enum drinks t;
    double amount = 0;
    if(argc != 2){
        fprintf(stderr, "Error! Usage: %s <file input>\n",argv[0]);
        return EXIT_FAILURE;
    }
    FILE * stream = fopen(argv[1], "r");
    if(stream == NULL){
        fprintf(stderr, "We cannot load the file!\n");
        return EXIT_FAILURE;
    }
    printf("done");
    while (fscanf(stream, "%d %lf\n", &t, &amount) != -1)
    {
        switch(t){
            case black_coffee:
                totalCaff += amount * 7.8;
                break;
            case black_tea:
                totalCaff += amount * 8.8;
                break;
            case green_tea:
                totalCaff += amount * 5.8;
                break;
            case white_tea:
                totalCaff += amount * 3.3;
                break;
            case iced_tea:
                totalCaff += amount * 7.8;
                break;
            case coke:
                totalCaff += amount * 2.5;
                break;
            default:
                break;
            printf("%lf", totalCaff);
        }
    }
    printf("%lf\n", totalCaff);
    if(flcose(stream)){
        fprintf(stderr, "Error is closing file!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}