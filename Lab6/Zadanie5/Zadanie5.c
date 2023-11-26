#include<stdio.h>

void convertToBinary(int n){

    if(n/2 != 0)
        convertToBinary(n/2);

    printf("%d",(n%2));

}

int main(){

    printf("Podaj liczbe w systemie dziesietnym:\n");

    int n;

    scanf("%d", &n);

    convertToBinary(n);

    return 0;

}
