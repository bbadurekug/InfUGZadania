#include<stdio.h>

int main(){

    int tab[10];

    int* p = tab;

    for(int i = 0; i < 10; i++){

        printf("Podaj %d. element tablicy\n", i);

        scanf("%d", p+i);

    }

    for(int i = 0; i < 10; i++){

        printf("%d. element tablicy to %d\n", i, *p+i);

    }

    return 0;

}
