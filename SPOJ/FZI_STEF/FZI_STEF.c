#include<stdio.h>

int main(){

    int n;
    scanf("%d", &n);

    int input[n];

    for(int i = 0; i < n; i++)
        scanf("%d", &input[i]);

    /*for(int i = 0; i < n; i++)
        printf("%d ", input[i]);*/

    long long int najwiekszy = 0;
    long long int aktualny = 0;

    int i = 0;

    while(i < n){

        if(aktualny > 0)
            aktualny += input[i];
        else
            aktualny = input[i];


        if(aktualny > najwiekszy)
            najwiekszy = aktualny;

        i++;

    }

    printf("%lld", najwiekszy);

    return 0;

}
