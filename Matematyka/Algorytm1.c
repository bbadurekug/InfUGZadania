#include<stdio.h>
#include<math.h>

int czy_liczba_jest_w_tablicy(int cyfra, int n, unsigned char tab[n]){

    char jest = 0;

    for(int i = 0; i < n; i++){

        if(tab[i] == cyfra){

            jest = 1;
            break;

        }

    }

    return jest;

}

void usuwanie_wiekszych(int cyfra, int n, unsigned char tab[n]){

    char wieksze[n];

    for(int i = 0; i < n; i++){                 //sprawdza ktore cyfry w liczbie sa wieksze

        if(tab[i] > cyfra){

            wieksze[i] = 1;

        }
        else

            wieksze[i] = 0;

    }

    int nowyTab[n];
    char nowyTabIndex = 0;

    for(int j = 0; j < n; j++){                 //tworzy nowa tablice bez wiekszych liczb

        if(wieksze[j] == 0){

            nowyTab[nowyTabIndex] = tab[j];
            nowyTabIndex++;

        }
        else{

            nowyTab[nowyTabIndex] = 0;
            nowyTabIndex++;

        }

    }


    for(int k = 0; k < n; k++){                 //wpisuje nowa tablice do starej

        tab[k] = nowyTab[k];

    }

}

void wstaw(int liczba, int n, unsigned char tab[n]){

    for(int i = 0; i < n; i++){

        if(tab[i] == 0){

            tab[i] = liczba;
            break;

        }

    }

}

void oblicz_podzbiory(char zbior[], char n){

    unsigned char podzbiory[n];

    for(int l = 0; l < n; l++){                         //zerowanie miejsc tablicy

        podzbiory[l] = 0;

    }

    printf("Podzbiory:\n");

    printf("{%c} ", 157);

    for(int i = 1; i < (int)pow(2,n); i++){

        for(int j = 1; j <= n; j++){                  //obliczanie podzbiorow

            if(!(czy_liczba_jest_w_tablicy(zbior[n-j], n, podzbiory))){

                wstaw(zbior[n-j], n, podzbiory);
                break;

            }
            else{

                usuwanie_wiekszych(zbior[n-(j+1)], n, podzbiory);

            }

        }

        printf("{");

        for(int m = 0; m < n; m++){

            if(podzbiory[m])
                printf("%d", podzbiory[m]);             //wypisywanie / jezeli 0, to nie wypisuje

        }

        printf("} ");
    }
}

int main(){

    unsigned char n;

    printf("Podaj dlugosc zbioru:\n");
    scanf("%hhu", &n);

    unsigned char zbior[n];

    for(int i=0; i < n; i++){

        zbior[i] = i+1;
    }

    printf("\nZbior:\n");


    for(int i=0; i < n; i++){

        printf("%d ", zbior[i]);
    }

    printf("\n\n");

    oblicz_podzbiory(zbior, n);

    return 0;

}
