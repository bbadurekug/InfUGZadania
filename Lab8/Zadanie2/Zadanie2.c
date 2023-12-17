#include<stdio.h>

#define SIZE    10
#define FALSE   0
#define TRUE    1

int przeszukiwanieBinarne(int tab[], int n){

    int left = 0;
    int right = SIZE-1;
    int result = FALSE;
    int middle;

    while(left <= right){

        middle = (left + right) / 2;

        if(tab[middle] < n)
            left = middle + 1;
        else if(tab[middle] > n)
            right = middle - 1;
        else{
            result = TRUE;
            break;
        }

    }

    return result;

}

int main(){

    int tablica[SIZE] = {110,252,423,434,534,569,743,823,856,998};

    int n;
    scanf("%d", &n);

    if(przeszukiwanieBinarne(tablica, n))
        printf("True\n");
    else
        printf("False\n");

    return 0;

}
