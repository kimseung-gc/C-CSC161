#include <stdio.h>
#include <stdlib.h>

struct boxL{
    double height;
    double length;
    double width;
    double volume;
    struct boxL * next;
};

typedef struct boxL boxL_t;

int main(){
    boxL_t * boxList = NULL;
    double h = 0;
    double l = 0;
    double w = 0;
    do{
        printf("Press 0 0 0 if you want to quit and print all the box values.\n");
        printf("Otherwise, input height, width, length of the box to be added.\n");
        scanf("%lf %lf %lf", &h, &w, &l);
        if(h > 0 && l > 0 && w > 0){
            boxL_t * temp = (boxL_t *)malloc(sizeof(boxL_t));
            temp->height = h;
            temp->width = w;
            temp->length = l;
            temp->volume = h*w*l;
            if(boxList == NULL){
                boxList = temp;
            }else{
                boxL_t * last = NULL;
                for(boxL_t * current = boxList; current != NULL; current = current->next){
                    if(current->next == NULL){
                        last = current;
                    }
                }
                last->next = temp;
            }
        }
    }while(h > 0 && l > 0 && w > 0);
    int i = 0;
    if(boxList == NULL){
        printf("The list is empty\n");
        return 0;
    }
    for(boxL_t * current = boxList; current != NULL; current = current->next){
        printf("box %d details \n", i+1);
        printf("height: %lf \n", current->height);
        printf("length: %lf \n", current->length);
        printf("width: %lf \n", current->width);
        printf("volume: %lf \n", current->volume);
        i++;
    }
    return 0;
}