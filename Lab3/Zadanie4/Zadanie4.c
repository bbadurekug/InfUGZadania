#include <stdio.h>

int main(){

    int a, b, c;

    printf("Podaj trzy liczby: \n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    if(a>b && a>c){

        printf("%d jest największe.", a);

    }
    else if(b>a && b>c){

        printf("%d jest największe.", b);

    }
    else{

        printf("%d jest największe.", c);

    }


}
