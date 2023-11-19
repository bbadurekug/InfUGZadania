#include<stdio.h>

char znak_napisu(char napis[100], int i){

    return napis[i-1];

}

int main(){

    char napis[100] = {0};
    unsigned int i;

    printf("Podaj napis:\n");
    scanf("%s", napis);

    printf("Ktory znak tego napisu chcesz wyswietlic:\n");
    scanf("%d", &i);

    printf("'%c' to %i znak napisu '%s'.\n",znak_napisu(napis, i), i, napis);

    return 0;

}
