#include<stdio.h>

int nwd(int a, int b){

    if(b > a){
        b += a;
        a = b - a;
        b -= a;
    }
    if(a == b)
        return a;
    else
        return nwd(a-b, b);

}


int main(){

    printf("Podaj dwie liczby:\n");

    int a,b;

    scanf("%d %d", &a, &b);

    printf("Najwiekszy wspolny dzielnik liczb %d i %d to %d.", a, b, nwd(a,b));

    return 0;

}
