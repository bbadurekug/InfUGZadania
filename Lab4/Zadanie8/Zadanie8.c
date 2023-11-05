#include<stdio.h>

int isPrime(n){

    if(n==1)
        return 0;

    for(int i = 2; i < n; i++){

        if(n%i == 0){

            return 0;
            break;

        }

    }

    return 1;

}

int main(){

    int a,b;
    int ilosc_pierwszych = 0;

    printf("Podaj pare liczb: \n");
    scanf("%d", &a);
    scanf("%d", &b);

    int pierwsze[b];

    for(int i = a; ilosc_pierwszych < b ;i++){

        if(isPrime(i)){

            pierwsze[ilosc_pierwszych] = i;
            ilosc_pierwszych++;

        }

    }

    printf("To jest %d liczb pierwszych wiekszych lub rownych %d:\n", b, a);

    for(int i = 0; i < b; i++){

        printf("%d\n", pierwsze[i]);

    }

    return 0;

}
