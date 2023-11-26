#include<stdio.h>

int fib(int n){

    return (n > 2)? fib(n-1) + fib(n-2): 1;

}

int main(){

    printf("Podaj liczbe:\n");

    int n;

    scanf("%d", &n);

    printf("Wyraz numer %d ciagu Fibonacciego to %d", n, fib(n));

    return 0;

}
