#include <stdio.h>
#include <string.h>

int
fibbo(int n){
    if(n==0||n==1){
        return 1;
    }
    return fibbo(n-2)+fibbo(n-1);
}

int main(int argc, char * argv[]){
    printf("%d\n", fibbo(5));
    for(int i = 0; i<argc;i++){
        printf("%c\n", (argv[i][strlen(argv[i])-1]));
    }
    return 0;
}