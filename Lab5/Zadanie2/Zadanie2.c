#include<stdio.h>

int znaki(char a, char b){

    return (a == b)? 1: 0;

}

int main(){

    printf("Podaj dwa znaki oddzielone spacja:\n");

    unsigned char a,b;

    scanf("%c %c", &a, &b);

    if(znaki(a,b) == 1)
        printf("%d: znaki sa identyczne.", znaki(a,b));
    else
        printf("%d: znaki nie sa identyczne.", znaki(a,b));

    return 0;

}
