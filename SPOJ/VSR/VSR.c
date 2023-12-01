#include<stdio.h>

int sredniaPredkosc(int a, int b){

    return (2*a*b) / (a+b);

}

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        int a,b;

        scanf("%d %d", &a, &b);

        printf("%d\n", sredniaPredkosc(a,b));


    }



}
