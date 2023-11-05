#include<stdio.h>

int main(){

    int a,b;
    int c = 1;
    int potega;

    printf("Podaj parę liczb naturalnych:\n");
    scanf("%d", &a);
    scanf("%d", &b);

    potega = a;

    for(; potega < b; c++){

        potega = potega * a;

    }

    printf("%d do potęgi %d jest większe od %d",a,c,b);


    return 0;

}
