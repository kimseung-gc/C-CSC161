#include <stdio.h>
#include <stdlib.h>

struct box{
    double height;
    double length;
    double width;
    double volume;
};

typedef struct box box_t;

int main(){
    box_t * arr = NULL;
    int n = 0;
    printf("How many boxes would you like? ");
    scanf("%d", &n);
    arr = (box_t *)malloc(n*sizeof(box_t));
    for(int i = 0; i < n; i++){
        double h, l, w;
        printf("Please input height, length, and width: ");
        scanf("%lf %lf %lf", &h, &l, &w);
        if(h <= 0||l <= 0||w <= 0){
            printf("Invalid Input\n");
            return -1;
        }
        arr[i].height = h;
        arr[i].length = l;
        arr[i].width = w;
        arr[i].volume = arr[i].height*arr[i].length*arr[i].width;
    }
    for(int i = 0; i<n; i++){
        printf("Box %d\n", i+1);
        printf("Height: %lf\n", arr[i].height);
        printf("Length: %lf\n", arr[i].length);
        printf("Width: %lf\n", arr[i].width);
        printf("Volume: %lf\n", arr[i].volume);
    }
    return 0;
}