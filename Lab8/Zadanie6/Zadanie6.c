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

int rosnaco(const void * a, const void * b){

    int _a = *(int*)a;
    int _b = *(int*)b;

    if(_a < _b)
        return -1;
    else if (_a > _b)
        return 1;
    else
        return 0;

}

void tabRand(int tab[]){

    for(int i = 0; i < size; i++)
        tab[i] = rand();

}

struct timespec timeStart = {0.0}, timeEnd = {0,0};

void czasFunkcjiSort(void(*funkcja)(int*), int tab[]){

    clock_gettime(CLOCK_MONOTONIC, &timeStart);
    funkcja(tab);
    clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    printf("%lld\n", (long long int)(timeEnd.tv_nsec- timeStart.tv_nsec));
}

void czasFunkcjiSearch(void(*funkcja)(int*, int), int tab[], int n){

    clock_gettime(CLOCK_MONOTONIC, &timeStart);
    funkcja(tab, n);
    clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    printf("%lld\n", (long long int)(timeEnd.tv_nsec- timeStart.tv_nsec));
}

int main(){

    int *tablica = NULL;
    srand(time(NULL));
    int n = rand();

    while(size < 10000){

        tablica = malloc(sizeof(int) * size);

        printf("\nDla %d elementow\n\n", size);

        tabRand(tablica);
        printf("Liniowe czas: ");
        czasFunkcjiSearch(&przeszukiwanieLiniowe, tablica, n);
        qsort(tablica, size, sizeof(int), rosnaco);
        tabRand(tablica);
        printf("Binarne czas: ");
        czasFunkcjiSearch(&przeszukiwanieBinarne, tablica, n);
        tabRand(tablica);
        printf("Babelkowe czas: ");
        czasFunkcjiSort(&sortowanieBabelkowe, tablica);
        tabRand(tablica);
        printf("Wstawianie czas: ");
        czasFunkcjiSort(&sortowaniePrzezWstawienie, tablica);
        tabRand(tablica);
        printf("Selekcja czas: ");
        czasFunkcjiSort(&sortowaniePrzezSelekcje, tablica);

        size *= 10;

        free(tablica);

    }

    printf("\n\nCzas podany w nanosekundach\n\n");

    return 0;

}
