#include<stdio.h>

void czy_palindrom(unsigned int n, char slowo[n]){

    char palindrom = 0;

    for(int i = 0; i < (n/2); i++){

        if(slowo[i] == slowo[(n-1) - i])
            palindrom++;

    }

    if(palindrom == (n/2))
        printf("Slowo '%s' jest palindromem", slowo);
    else
        printf("Slowo '%s' nie jest palindromem", slowo);

}

int main(){

    unsigned int n;

    printf("Podaj dlugosc twojego slowa:\n");
    scanf("%d", &n);

    char slowo[n];

    printf("Podaj slowo:\n");
    scanf("%s", slowo);

    czy_palindrom(n, slowo);

    return 0;

}
