#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int czy_liczba_jest_w_tablicy(int cyfra, int x, int y, int tab[x][y]){

    char jest = 0;

    for(int i = 0; i < y; i++){

        if(tab[x][i] == cyfra){
            jest = 1;
        }

    }

    return jest;

}

void usuwanie_wiekszych(int cyfra, int x , int y, int tab[x][y]){

    char wieksze[y];

    for(int i = 0; i < y; i++){                 //sprawdza ktore cyfry w liczbie sa wieksze

        if(tab[x][i] > cyfra){

            wieksze[i] = 1;

        }
        else
            wieksze[i] = 0;

    }

    int nowyTab[y];
    char nowyTabIndex = 0;

    for(int j = 0; j < y; j++){                 //tworzy nowa tablice bez wiekszych liczb

        if(wieksze[j] == 0){

            nowyTab[nowyTabIndex] = tab[x][j];
            nowyTabIndex++;

        }
        else{

            nowyTab[nowyTabIndex] = 0;
            nowyTabIndex++;
        }

    }


    for(int k = 0; k < y; k++){                 //wpisuje nowa tablice do starej

        tab[x][k] = nowyTab[k];

    }

}

void wstaw(int liczba, int x, int y, int tab[x][y]){

    for(int i = 0; i < y; i++){

        if(tab[x][i] == 0){
            tab[x][i] = liczba;
            break;
        }

    }

}

void oblicz_podzbiory(char zbior[], int n){

    int kolumny = (int)pow(2,n), wiersze = n;

    int podzbiory[kolumny][wiersze];

    for(int zX = 0; zX < kolumny; zX++){            //zerowanie miejsc tablicy

        for(int zY = 0; zY < wiersze; zY++){

            podzbiory[zX][zY] = 0;

        }
    }


    for(int i = 1; i < kolumny; i++){               //obliczanie podzbiorow

        for(int j = 1; j <= wiersze; j++){

            if(!(czy_liczba_jest_w_tablicy(zbior[n-j], i, wiersze, podzbiory))){

                wstaw(zbior[n-j], i, wiersze, podzbiory);
                break;

            }
            else{

                usuwanie_wiekszych(zbior[n-(j+1)], i, wiersze, podzbiory);

            }

        }
        if(i+1 < kolumny){

            for(int k = 0; k < wiersze; k++){

                podzbiory[i+1][k] = podzbiory[i][k];

            }

        }
    }

    podzbiory[0][0] = 157;                           //znak pustego zbioru

    printf("Podzbiory:\n");

    for(int zX = 0; zX < kolumny; zX++){             //wypisywanie tablicy

        printf("{");

        for(int zY = 0; zY < wiersze; zY++){

            if(podzbiory[zX][zY] != 0){
                if(zX)
                    printf("%d", podzbiory[zX][zY]);
                else
                    printf("%c", podzbiory[zX][zY]);
            }

        }

        printf("}, ");

    }

}

int main(){

    int n;

    scanf("%d", &n);

    char zbior[n];

    for(int i=1; i <= n; i++){

        zbior[i-1] = i;
    }

    printf("\nZbior:\n");


    for(int i=0; i < n; i++){

        printf("%d ", zbior[i]);
    }

    printf("\n\n");

    oblicz_podzbiory(zbior, n);

    return EXIT_SUCCESS;

}
