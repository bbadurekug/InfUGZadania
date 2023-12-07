#include<stdio.h>

void odwrot(int n){

    int liczba;

    if(n != 0){
        scanf("%d", &liczba);

        odwrot(n-1);

        printf("%d ", liczba);
    }
    else
        printf("Twoje liczby od tylu:\n");

}

int main(){

    int n;

    printf("Ile liczb chcesz wypisac od tylu:\n");

    scanf("%d", &n);

    printf("Podaj twoje liczby:\n");

    odwrot(n);

    return 0;

}
