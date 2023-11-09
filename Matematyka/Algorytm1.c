#include<stdio.h>

int potegowanie(int a, int b){

    int wynik;

    wynik = a;

    if(b == 0){

        wynik = 1;

    }
    else{

        for(int i = 1; i < b; i++){

            wynik = wynik * a;

        }
    }

    return wynik;
}

int max(int tab[], int dlugoscTab){

    int najwiekszy = tab[0];

    for(int i = 0; i < (dlugoscTab - 1); i++){

        if(tab[i] > tab[i+1] && tab[i] > najwiekszy){

            najwiekszy = tab[i];

        }
        else if(tab[i+1] > tab[i] && tab[i+1] > najwiekszy){

            najwiekszy = tab[i+1];

        }

    }

    return najwiekszy;
}

int main(){

    int n;

    printf("Podaj dlugosc zbioru:\n");
    scanf("%d", &n);

    int zbior[n];

    int podzbiory[potegowanie(2,n)][n];

    for(int i1=0; i1 < potegowanie(2,n); i1++){               //zeruje miejsca w tablicy

        for(int i2=0; i2 < n; i2++){

            podzbiory[i1][i2] = 0;

        }

    }

    printf("Podaj elementy zbioru:\n");

    for(int i = 0; i < n; i++){

        scanf("%d", &zbior[i]);

    }

    printf("\n");
    printf("Zbior:\n");

    for(int i = 0; i < n; i++){

        printf("%d ", zbior[i]);

    }

    podzbiory[0][0] = 157;                      //znak pustego zbioru w ASCII

    for(int i1=1; i1 < potegowanie(2,n); i1++){

        for(int i2=0; i2 < n; i2++){

            podzbiory[i1][i2] = max(zbior, n);

        }

    }


    printf("\n");
    printf("\n");

    printf("Podzbiory: \n");

    for(int i1=0; i1 < potegowanie(2,n); i1++){

        for(int i2=0; i2 < n; i2++){

            printf("%d ", podzbiory[i1][i2]);

        }

        printf("\n");

    }

    return 0;

}
