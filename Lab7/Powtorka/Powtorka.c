#include<stdio.h>
#include<stdlib.h>

#define SIZE    10

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

typedef struct drzewo{

    int index;
    char ojciec;
    int lewySyn;
    int prawySyn;


} Drzewo;

void drzewoBinarne(char* pTab){

    int i = 0;

    Drzewo drzewo[n];

    for(int j = 0; j < n; j++){

        drzewo[j].index = j;
        drzewo[j].ojciec = *(pTab+j);
        drzewo[j].lewySyn = -1;
        drzewo[j].prawySyn = -1;

    }

    for(int j = 1; j < n; j++){

        int sprawdzana = 0;

        while(sprawdzana != -1){

            //printf("porownuje %d %d\n", j, sprawdzana);

            if(*(pTab+j) < pTab[sprawdzana]){
                //printf("%d mniejsze\n", j);
                if(drzewo[sprawdzana].lewySyn == -1){
                    drzewo[sprawdzana].lewySyn = j;
                    sprawdzana = -1;
                }
                else{
                    sprawdzana = drzewo[sprawdzana].lewySyn;
                }
            }
            else{
                //printf("%d wieksze\n", j);
                if(drzewo[sprawdzana].prawySyn == -1){
                    drzewo[sprawdzana].prawySyn = j;
                    sprawdzana = -1;
                }
                else{
                    sprawdzana = drzewo[sprawdzana].prawySyn;
                }
            }
        }
    }

    for(int i = 0; i < n; i++){

        printf("ojciec:%c lewy:%d prawy:%d\n", drzewo[i].ojciec, drzewo[i].lewySyn, drzewo[i].prawySyn);


    }

    printf("          %c \n", drzewo[i].ojciec);

    int ileSpacji = 9;
    int ileWypisywac = 1;
    int ileWypisano = 0;

    for(int i = 0; i < n; i++){

        if(ileWypisano == 0){
            for(int s = 0; s < ileSpacji; s++)
                printf(" ");
        ileSpacji--;
        }


        int j;

        j = drzewo[i].lewySyn;

        if(drzewo[i].lewySyn != -1)
            printf("%c ", drzewo[j].ojciec);
        else
            printf("  ");

        j = drzewo[i].prawySyn;

        if(drzewo[i].prawySyn != -1)
            printf("%c ", drzewo[j].ojciec);
        else
            printf("  ");

        ileWypisano++;

        if(ileWypisano == ileWypisywac){
            printf("\n");
            ileWypisywac *= 2;
            ileWypisano = 0;
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
