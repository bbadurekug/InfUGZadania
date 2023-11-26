#include <stdio.h>

#define size    10

void sortA(int tab[], int n){

    static int index = 0;

    if(index == size)
        printf("Liczba %d nie znajduje sie w tablicy", n);
    else{

        if(tab[index] == n)
            printf("Liczba %d jest na %d miejscu tablicy\n", n, index);
        else{
            index++;
            sortA(tab, n);
        }
    }
}

void sortB(int tab[], int n){

    static int prawaGranica = 9;
    static int lewaGranica = 0;
    static int pivot = (size-1)/2;
    //printf("%d ", index);

    if(tab[pivot] < n){

            lewaGranica = pivot;

            if((prawaGranica - lewaGranica)/2 != 0)
                pivot += (prawaGranica - lewaGranica)/2;
            else
                pivot++;

            sortB(tab, n);

        }

    else if(tab[pivot] > n){

            prawaGranica = pivot;

            if((prawaGranica - lewaGranica)/2 != 0)
                pivot -= (prawaGranica - lewaGranica)/2;
            else
                pivot--;

            sortB(tab, n);

        }
    else
        printf("Liczba %d znajduje sie w tablicy.", n);


}

int main(){

    unsigned int tab[size] = {2,4,6,12,24,25,34,42,67,99};

    printf("Podaj liczbe ktora chcesz znalesc w tablicy:\n");

    int n;

    scanf("%d", &n);

    sortB(tab, n);

    return 0;

}
