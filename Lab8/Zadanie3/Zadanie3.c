#include<stdio.h>

#define SIZE    10
#define FALSE   0
#define TRUE    1

void sortowanieBabelkowe(int tab[]){

    int i = SIZE-1;
    int j;
    int temp = 0;

    while(i != -1){  //raczej -1

        j = 0;

        while(j < i){

            if(tab[j+1] < tab[j]){

                temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;

            }

            j++;

        }

        i--;

    }



}

int main(){

    int tablica[SIZE] = {761,25232,423,434,5345,564,237,128,349,1210};

    sortowanieBabelkowe(tablica);

    for(int i = 0; i < SIZE; i++)
        printf("%d ", tablica[i]);

    return 0;

}
