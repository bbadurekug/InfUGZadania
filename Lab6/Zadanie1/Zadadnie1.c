#include<stdio.h>

int silnia(int n){

    if(n <= 0)
        return 1;

    return n*silnia(n-1);

}

int main(){

    printf("Podaj liczbe:\n");

    int n;

    scanf("%d", &n);

    //printf("%d", n);

    printf("%d! to %d", n, silnia(n));

    return 0;

}
