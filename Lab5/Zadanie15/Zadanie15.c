#include<stdio.h>

void wypisz_tablice_w_ramce(int n, unsigned char znaki[n]){

    printf("\u250F");

    for(int i = 0; i < n; i++){

        printf("\u2501");

    }

    printf("\u2513\n");

    printf("\u2503");

    for(int j = 0; j < n; j++){

        printf("%c", znaki[j]);

    }

    printf("\u2503\n");

    printf("\u2517");

    for(int k = 0; k < n; k++){

        printf("\u2501");

    }

    printf("\u251B");

}

int main(){

    int n;

    printf("Ile znakow chcesz wpisac w talbice:\n");
    scanf("%d", &n);

    char znaki[n];

    printf("Wpisz slowo:\n");

    scanf("%s", znaki);

    printf("\n");

    wypisz_tablice_w_ramce(n,znaki);

    return 0;

}
