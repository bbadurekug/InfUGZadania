#include<stdio.h>

#define SIZE    10

int rozmiarTablicy(int* pFirst, int* pLast){

    int pSize = (pLast - pFirst) + 1;

    for(int i = 0; i < pSize; i++){

        *pFirst = i+1;
        printf("%d ", *pFirst);
        pFirst++;

    }

    printf("\n");

    return pSize;

}

int main(){

    int tab[SIZE];

    printf("Rozmiar tablicy to %d\n", rozmiarTablicy(&tab[0], &tab[SIZE-1]));

    return 0;

}
