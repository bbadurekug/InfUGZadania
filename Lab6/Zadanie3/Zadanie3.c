#include<stdio.h>

int suma(int n){

    return (n != 0)? n+suma(n-1): n;

}

int main(){

    printf("Podaj liczbe\n");

    int n;

    scanf("%d", &n);

    printf("Suma liczb z przedzialu od 1 do %d wynosi %d", n, suma(n));

    return 0;

}
