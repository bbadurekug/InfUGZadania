#include<stdio.h>

int main(){

    int n;
    int kwadrat = 0;

    printf("Podaj liczbę naturalną: \n");
    scanf("%d", &n);

    for(int i = 1; i < n; i++){

        kwadrat = i*i;
        printf("Kwadrat liczby %d to %d \n", i, kwadrat);

    }

    return 0;

}
