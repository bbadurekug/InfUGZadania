#include<stdio.h>

int znajdzNajwiekszy(int* pTab, int size){

    int najwiekszy = 0;
    int najIndex = 0;

    for(int i = 0; i < size; i++){

        if(*pTab > najwiekszy){

            najwiekszy = *pTab;
            najIndex = i;

        }

        pTab++;

    }

    pTab -= size;
    pTab += najIndex;

    *pTab = 0;

    return najwiekszy;

}

int main(){

    int size = 10;

    int tab[10] = {4, 12, 1, 13, 34, 2, 15, 9, 10, 23};

    printf("Tablica przed:\n");

    for(int i = 0; i < size; i++){

        printf("%d ", tab[i]);

    }

    printf("\n\n");

    printf("najwiekszy: %d\n\n", znajdzNajwiekszy(&tab[0], size));

    printf("Tablica po:\n");

    for(int i = 0; i < size; i++){

        printf("%d ", tab[i]);

    }

    printf("\n");

    return 0;

}
