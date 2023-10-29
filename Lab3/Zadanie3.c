#include <stdio.h>

int main(){

    int a, b;

    printf("Podaj dwie liczby: \n");
    scanf("%d", &a);
    scanf("%d", &b);

    if(a>b){

        printf("%d jest większe od %d.", a, b);

    }
    else{

        printf("%d jest większe od %d.", b, a);

    }

}
