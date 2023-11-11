#include<stdio.h>

int main(){

    int suma = 15;

    int pomocna = 0, sumaZgadniec = 0;

    short zgadniecie[4] = {0,0,0,0};

    printf("Zgadnij liczbe od 1 do 5:\n");

    for(int i = 0; i < 4; i++){

        label:

        scanf("%d", &pomocna);

        while(pomocna > 5){

            printf("Podana liczba jest wieksza od 5. Sprobuj ponownie:\n");
            goto label;

        }

        for(int i = 0; i < 4; i++){

            if(pomocna == zgadniecie[i]){

                printf("Juz probowales te liczbe. Wybierz inna:\n");
                goto label;
            }

        }

        zgadniecie[i] = pomocna;
        sumaZgadniec += pomocna;

    }

    printf("Poprawna odpowiedz to %d!", suma - sumaZgadniec);

    return 0;

}
