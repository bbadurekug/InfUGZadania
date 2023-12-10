#include<stdio.h>
#include<stdlib.h>

#define SIZE    5

int n = 0;

void wypiszElementy(char* pTab){

    if(n == 0)
        printf("Blad! Pusta tablica\n");
    else
        printf("Twoja tablica:\n%s\n", pTab);

}

void wstawElement(char* pTab){

    for(int i = 0; i < SIZE; i++){

        if(*pTab == '\0'){

            printf("Podaj liczbe, ktora chcesz wstawic do talicy:\n");
            scanf(" %c", pTab);

            if(*pTab > 57 || *pTab < 47){

                printf("Blad! To nie jest liczba");
                *pTab = '\0';

            }
            else{
                pTab++;
                *pTab = '\0';
            }

            n++;
            return;

        }

        pTab++;
    }

    printf("Brak miejsca w tablicy!\n");

}

void usunElement(char* pTab){

    int index;

    printf("Podaj indeks elementu, ktory chcesz usunac:\n");
    scanf("%d", &index);

    for(int i = index; i < SIZE; i++)
        *(pTab+i) = *(pTab+(i+1));

    n--;

}

int sumaElementow(char* pTab){

    int suma = 0;

    for(int i = 0; i < n; i++){

        //printf("cyfra: %c\n", *pTab);
        suma += *pTab - 48;
        pTab++;
        //printf("suma: %d\n", suma);

    }

    return (n != 0)? suma: -1;
}

typedef struct korzen{

    char ojciec;
    char* lewySyn;
    char* prawySyn;

} Korzen;


void drzewoBinarne(char* pTab){

    Korzen drzewo[n];

    for(int i = 0; i < n; i++){

        drzewo[i].ojciec = *(pTab+i);
        drzewo[i].lewySyn = NULL;
        drzewo[i].prawySyn = NULL;

        if(i != 0){



        }

    }


}

int main(){

    char tab[SIZE+1];

    int wybor;

    while(1){

        printf("Wybierz jedna z opcji\n0 - zakoncz dzialanie programu\n1 - wypisz elementy tablicy\n2 - wstaw nowy element\n3 - usun element\n4 - wyswietl sume znakow\n5 - wyswietl drzewo binarne\n\n");

        scanf("%d", &wybor);

        switch(wybor){

            case 0:
                printf("Zakanczam dzialanie programu.\n");
                return 0;

            case 1:
                wypiszElementy(tab);
                break;

            case 2:
                wstawElement(tab);
                break;

            case 3:
                usunElement(tab);
                break;

            case 4:
                if(sumaElementow(tab) == -1)
                    printf("Blad! Tablica jest pusta!\n");
                else
                    printf("Suma wszystkich elementow wynosi %d\n", sumaElementow(tab));
                break;

            case 5:
                drzewoBinarne(tab);
                break;

            default:
                printf("Bledny wybor!\n");
                break;

        }

        printf("\n");

    }

    return 0;

}
