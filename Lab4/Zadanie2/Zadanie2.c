#include<stdio.h>

int main(){

    int a,b;
    int potega;

    printf("Podaj parę liczb naturalnych:\n");
    scanf("%d", &a);
    scanf("%d", &b);

    potega = a;

    for(int i = 1; i < b; i++){

        potega = potega * a;

    }

    printf("%d do potęgi %d jest równe %d", a, b, potega);

    return 0;

}
