#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define FALSE   0
#define TRUE    1

int size = 50000;

void sortowanieBabelkowe(int tab[]){

    int i = size-1;
    int j;
    int temp = 0;

    while(i != -1){

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

int malejaco(const void * a, const void * b){

    int _a = *(int*)a;
    int _b = *(int*)b;

    if(_a > _b)
        return -1;
    else if (_a < _b)
        return 1;
    else
        return 0;

}

struct timespec timeStart = {0.0}, timeEnd = {0,0};

void czasFunkcji(void(*funkcja)(int*), int tab[]){

    clock_gettime(CLOCK_MONOTONIC, &timeStart);
    funkcja(tab);
    clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    printf("%lld\n", (long long int)(timeEnd.tv_sec- timeStart.tv_sec));
}

int main(){

    int *tablica = NULL;
    srand(time(NULL));
    int n = rand();

    tablica = malloc(sizeof(int) * size);

    printf("\nDla %d losowych elementow\n\n", size);
    tabRand(tablica);
    printf("Babelkowe czas: ");
    czasFunkcji(&sortowanieBabelkowe, tablica);
    tabRand(tablica);
    printf("Wstawianie czas: ");
    czasFunkcji(&sortowaniePrzezWstawienie, tablica);
    tabRand(tablica);
    printf("Selekcja czas: ");
    czasFunkcji(&sortowaniePrzezSelekcje, tablica);

    printf("\nDla %d posortowanych elementow\n\n", size);
    printf("Babelkowe czas: ");
    czasFunkcji(&sortowanieBabelkowe, tablica);
    printf("Wstawianie czas: ");
    czasFunkcji(&sortowaniePrzezWstawienie, tablica);
    printf("Selekcja czas: ");
    czasFunkcji(&sortowaniePrzezSelekcje, tablica);

    printf("\nDla %d odwrotnie posortowanych elementow\n\n", size);
    qsort(tablica, size, sizeof(int), malejaco);
    printf("Babelkowe czas: ");
    czasFunkcji(&sortowanieBabelkowe, tablica);
    printf("Wstawianie czas: ");
    czasFunkcji(&sortowaniePrzezWstawienie, tablica);
    printf("Selekcja czas: ");
    czasFunkcji(&sortowaniePrzezSelekcje, tablica);

    free(tablica);

    printf("\n\nCzas podany w sekundach\n\n");

    return 0;

}
