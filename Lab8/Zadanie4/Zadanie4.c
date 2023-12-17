#include<stdio.h>

#define SIZE    10
#define FALSE   0
#define TRUE    1

void sortowaniePrzezWstawienie(int tab[]){

    int i = 0;
    int k;
    int element;

    while(i <= (SIZE-1)){

        element = tab[i];
        k = i - 1;

        while(k >= 0 && tab[k] > element){

            tab[k+1] = tab[k];
            k--;

        }

        tab[k+1] = element;
        i++;

    }

}

int main(){

    int tablica[SIZE] = {761,232,4232,434,5345,564,27,128,349,110};

    sortowaniePrzezWstawienie(tablica);

    for(int i = 0; i < SIZE; i++)
        printf("%d ", tablica[i]);

    return 0;

}
