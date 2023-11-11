#include<stdio.h>

int main(){

    int n;

    printf("Podaj ilosc kolumn tabeli ASCII:\n");
    scanf("%d", &n);

    int ascii[n];

    for(int i = 0; i <= n; i++){

        ascii[i] = i;

    }

    for(int i = 0; i <= n; i++){

        printf("%c\n", ascii[i]);

    }

    return 0;

}
