#include<stdio.h>

int sumaCyfr(int n){

    return (n != 0)? n%10 + sumaCyfr(n/10): n;

}

int main(){

    printf("Podaj liczbe:\n");

    int n;

    scanf("%d", &n);

    printf("Suma cyfr liczby %d to %d", n, sumaCyfr(n));

    return 0;

}
