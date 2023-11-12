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


void obliczPodzbiory(short zbior[], int n){

    int podzbiory[(int)pow(2,n)];

    podzbiory[0] = 157;

    for(int i = 1; i < (int)pow(2,n); i++){

        if(!(czyAjestwB(zbior[n-i], podzbiory[i-1]))){

            podzbiory[i] = zbior[n-i];

        }
        else{

            podzbiory[i] = zbior[n-(i-1)];

        }
    }

    for(int i=0; i < (int)pow(2,n); i++){

        printf("%d ", podzbiory[i]);
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
