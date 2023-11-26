#include<stdio.h>

int silnia(int n){

    if(n <= 0)
        return 1;

    n *= silnia(n-1);

    return n;

}

int nwd(int a, int b){

    if(b > a){
        b += a;
        a = b - a;
        b -= a;
    }
    if(a == b)
        return a;
    else
        a = nwd(a-b, b);

}

int suma(int n){

    static int i = 0;
    static int wynik = 0;

    if(n-i != 0){
        wynik += n-i;
        //printf("i:%d wynik:%d \n", i,wynik);
        i++;
        suma(n);
    }
    else
        return wynik;

    //return (n != 0)? n+suma(n-1): n;

}

int fib(int n){

    static int wynik = 0;
    static int i = 1;

    if(i <= n){

        if(i <= 2){
            wynik = 1;
            printf("i:%d wynik:%dgora\n:", i, wynik);
            i++;
            fib(n);
        }
        else{
            wynik += fib(n-1);
            printf("i:%d wynik:%d dol\n:", i, wynik);
            i++;
            //fib(i);
        }
    }
    else
        return wynik;

}

int main(){

    printf("Podaj liczbe:\n");

    int n;

    scanf("%d", &n);

    printf("Wyraz numer %d ciagu Fibonacciego to %d", n, fib(n));

    return 0;

}
