#include<stdio.h>

int main(){

    int dlugosc;
    int wartosc;

    printf("Jak długa ma być tablica?\n");
    scanf("%d", &dlugosc);

    int tablica[dlugosc];

    for(int i = 0; i < dlugosc; i++){

        printf("Podaj wartość %d elementu tablicy: \n", i);
        scanf(" %d", &wartosc);
        tablica[i] = wartosc;

    }

    printf("Twoja tablica to:\n");

    for(int i = 0; i < dlugosc; i++){

        printf("%d\n", tablica[i]);

    }

    return 0;

}


//TO JEST ZADANIE 5
