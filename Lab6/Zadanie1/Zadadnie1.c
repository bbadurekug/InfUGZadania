#include<stdio.h>

int silnia(int n){

    if(n <= 0)
        return 1;

    return n*silnia(n-1);

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


int main(){

    printf("Podaj dwie liczby:\n");

    int a,b;

    scanf("%d %d", &a, &b);

    printf("Najwiekszy wspolny dzielnik liczb %d i %d to %d.", a, b, nwd(a,b));

    return 0;

}
