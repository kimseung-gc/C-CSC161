#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum drinks {black_coffee, black_tea, green_tea, white_tea, iced_tea, coke};

int main(){
    enum drinks drInp = -1;
    double totalCaf = 0.0;
    do{
        double amount = 0;
        printf("What have you drank?\n");
        printf("1. black_coffee\n");
        printf("2. black_tea\n");
        printf("3. green_tea\n");
        printf("4. white_tea\n");
        printf("5. iced_tea\n");
        printf("6. coke\n");
        printf("7. None\n");
        scanf("%d", &drInp);
        printf("How much did you drink?\n");
        scanf("%d", &amount);
        switch (drInp-1)
        {
            case black_coffee:
                totalCaf += amount * 150.0;
                break;
            case black_tea:
                totalCaf += amount * 150.0;
                break;
            case green_tea:
                totalCaf += amount * 150.0;
                break;
            case white_tea:
                totalCaf += amount * 150.0;
                break;
            case iced_tea:
                totalCaf += amount * 150.0;
                break;
            case coke:
                totalCaf += amount * 300.0;
                break;
            case 6:
                break;
            default:
                fprintf(stderr, "Invalid input! Please try again\n");
                fflush(stdin);
            break;
        }
    }while(drInp != 7);
    printf("You drank %f amount of caffeine today!\n", totalCaf);
    return 0;
}