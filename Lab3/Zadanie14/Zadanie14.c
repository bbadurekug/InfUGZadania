#include<stdio.h>

int main(){

    printf("Podaj kat:\n");

    short kat;

    scanf("%d", &kat);

    float rad;

    rad = kat/180.f;

    printf("%d stopni to %.2f Pi radianow.", kat, rad);

    return 0;

}
