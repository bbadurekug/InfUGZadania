#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int czyAjestwB(int a, int b){

    int jest=0;

    for(int i = 0; i < log10(b)+1; i++){

        if((b/(int)pow(10, i) - b/(int)pow(10, i+1) * 10) == a){

            jest = 1;

        }

    }

    return jest;

}

int usuwanieWiekszych(int cyfra, int liczbaSprawdzana, int n){

    int dlugoscTab = (int)log10(liczbaSprawdzana)+1;

    int wieksze[dlugoscTab];


    for(int i = 0; i < n; i++){

        if((liczbaSprawdzana/(int)pow(10, n-(i+1)) - liczbaSprawdzana/(int)pow(10, n-i) * 10) > cyfra){

            wieksze[i] = 1;

        }
        else
            wieksze[i] = 0;

    }

    //SPRAWDZA KTORE CYFRY W LICZBIE SA WIEKSZE

    int nowaLiczba, staraLiczba;

    staraLiczba = liczbaSprawdzana;

    for(int j = 0; j < n; j++){

        if(wieksze[j] == 1){

            staraLiczba -= staraLiczba/(int)pow(10, n-(j+1)) - staraLiczba/(int)pow(10, n-j) * 10;
            staraLiczba /= 10;

        }

    }

    nowaLiczba = staraLiczba;

    return nowaLiczba;

    //USUWA TE CYFRY KTORE SA WIEKSZE

}


void obliczPodzbiory(short zbior[], int n){

    int podzbiory[(int)pow(2,n)];

    podzbiory[0] = 0;

    for(int i = 1; i < (int)pow(2,n); i++){

        if(!(czyAjestwB(zbior[n-1], podzbiory[i-1]))){

            podzbiory[i] = zbior[n-1];

        }
        else{

            podzbiory[i] = usuwanieWiekszych(zbior[n-2],podzbiory[i-1],n) * 10 + zbior[n-2];

        }

    }




    podzbiory[0] = 157;

    for(int i=0; i < (int)pow(2,n); i++){

        if(i)
            printf("%d ", podzbiory[i]);
        else
            printf("%c ", podzbiory[i]);
    }

}

int main(){

    int n;

    printf("Podaj dlugosc zbioru:\n");
    scanf("%d", &n);

    short zbior[n];

    for(int i=1; i <= n; i++){

        zbior[i-1] = i;
    }


    for(int i=0; i < n; i++){

        printf("%d ", zbior[i]);
    }

    printf("\n\n");

    obliczPodzbiory(zbior, n);

    return 0;

}
