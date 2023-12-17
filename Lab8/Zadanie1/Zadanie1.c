#include<stdio.h>

#define SIZE    10
#define FALSE   0
#define TRUE    1

int przeszukiwanieLiniowe(int tab[], int n){

    int index = 0; //zaczyna od 1 w pseudokodzie
    int wynik = FALSE;

    while(index <= SIZE){

        if(tab[index] == n)
            wynik = TRUE;

        index++;

    }

    return wynik;

}

int main(){

    int tablica[SIZE] = {761,252,423,434,5345,56,237,128,349,110};

    int n;
    scanf("%d", &n);

    if(przeszukiwanieLiniowe(tablica, n))
        printf("True\n");
    else
        printf("False\n");

    return 0;

}
