#include<stdio.h>

void printfloat(float x){

    for(int i = sizeof(x)-1; i >= 0; --i){

        printf("%x ",((unsigned char*)&x)[i]);

    }

}

int main(){

    int t;
    float x;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        scanf("%f", &x);
        printfloat(x);

    }

    return 0;

}
