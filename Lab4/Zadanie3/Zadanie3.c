#include<stdio.h>

int main(){

    int dlugosc;

    printf("Jak długa ma być tablica?\n");
    scanf("%d", &dlugosc);

    int tablica[dlugosc];

    for(int i = 0; i < dlugosc; i++){

        tablica[i] = i+1;

    }

    for(int i = 0; i < dlugosc; i++){

        printf("%d\n", tablica[i]*tablica[i]);

    }


    return 0;

}
