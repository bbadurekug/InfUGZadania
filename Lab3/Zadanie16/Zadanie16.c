#include<stdio.h>

int main(){

    int suma = 15;

    int pomocna = 0, sumaZgadniec = 0;

    printf("Zgadnij liczbe od 1 do 5:\n");

    for(int i = 0; i < 4; i++){

        scanf("%d", &pomocna);
        printf("Zla odpowiedz!\n");
        sumaZgadniec += pomocna;

    }

    printf("Poprawna odpowiedz to %d!", suma - sumaZgadniec);

    return 0;

}
