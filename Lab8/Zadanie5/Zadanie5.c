#include<stdio.h>

#define SIZE    10
#define FALSE   0
#define TRUE    1

int min(int tab[], int start){

    int minIndex = start;

    for(int i = start; i < SIZE; i++){

        if(tab[i] < tab[minIndex])
            minIndex = i;

    }

    return minIndex;

}

void sortowaniePrzezSelekcje(int tab[]){

    int i = 0;
    int temp;
    int minIndex;

    while(i < SIZE){

        minIndex = min(tab, i);

        temp = tab[i];
        tab[i] = tab[minIndex];
        tab[minIndex] = temp;

        i++;

    }

}

int main(){

    int tablica[SIZE] = {761,232,4232,434,5345,564,227,128,349,110};

    sortowaniePrzezSelekcje(tablica);

    for(int i = 0; i < SIZE; i++)
        printf("%d ", tablica[i]);

    return 0;

}
