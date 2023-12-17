#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define FALSE   0
#define TRUE    1

int size = 10;

void przeszukiwanieLiniowe(int tab[], int n){

    int index = 0; //zaczyna od 1 w pseudokodzie
    int wynik = FALSE;

    while(index <= size){

        if(tab[index] == n)
            wynik = TRUE;

        index++;

    }

    /*if(wynik)
        printf("TRUE\n");
    else
        printf("FALSE\n");*/

}

void przeszukiwanieBinarne(int tab[], int n){

    int left = 0;
    int right = size-1;
    int result = FALSE;
    int middle;

    while(left <= right){

        middle = (left + right) / 2;

        if(tab[middle] < n)
            left = middle + 1;
        else if(tab[middle] > n)
            right = middle - 1;
        else{
            result = TRUE;
            break;
        }

    }

    /*if(result)
        printf("TRUE\n");
    else
        printf("FALSE\n");*/

}

void sortowanieBabelkowe(int tab[]){

    int i = size-1;
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

void sortowaniePrzezWstawienie(int tab[]){

    int i = 0;
    int k;
    int element;

    while(i <= (size-1)){

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

int min(int tab[], int start){

    int minIndex = start;

    for(int i = start; i < size; i++){

        if(tab[i] < tab[minIndex])
            minIndex = i;

    }

    return minIndex;

}

void sortowaniePrzezSelekcje(int tab[]){

    int i = 0;
    int temp;
    int minIndex;

    while(i < size){

        minIndex = min(tab, i);

        temp = tab[i];
        tab[i] = tab[minIndex];
        tab[minIndex] = temp;

        i++;

    }

}

void tabRand(int tab[]){

    for(int i = 0; i < size; i++)
        tab[i] = rand();

}

int main(){

    int *tablica = NULL;

    srand(time(NULL));

    int n = rand();

    struct timespec timeStart = {0.0}, timeEnd = {0,0};

    while(size < 100000){

        tablica = malloc(sizeof(int) * size);

        printf("\nDla %d elementow\n\n", size);

        tabRand(tablica);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);
        przeszukiwanieLiniowe(tablica, n);
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        printf("Liniowe czas: %lld\n", (long long int)(timeEnd.tv_nsec- timeStart.tv_nsec));

        sortowaniePrzezSelekcje(tablica);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);
        przeszukiwanieBinarne(tablica, n);
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        printf("Binarne czas: %lld\n", (long long int)(timeEnd.tv_nsec- timeStart.tv_nsec));

        tabRand(tablica);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);
        sortowanieBabelkowe(tablica);
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        printf("Babelkowe czas: %lld\n", (long long int)(timeEnd.tv_nsec- timeStart.tv_nsec));

        tabRand(tablica);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);
        sortowaniePrzezWstawienie(tablica);
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        printf("Wstawianie czas: %lld\n", (long long int)(timeEnd.tv_nsec- timeStart.tv_nsec));

        tabRand(tablica);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);
        sortowaniePrzezSelekcje(tablica);
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        printf("Selekcja czas: %lld\n", (long long int)(timeEnd.tv_nsec- timeStart.tv_nsec));

        size *= 10;

        free(tablica);

    }

    return 0;

}
