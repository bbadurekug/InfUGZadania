#include<stdio.h>

int globalna = 10;

void adresy(int* a, int* b){

    printf("adres a: %p adres b: %p\n", a, b);

}

int main(){

    int lokalna = globalna;

    printf("adres globalnej: %p adres lokalnej: %p\n", &globalna, &lokalna);

    adresy(&globalna, &lokalna);

    return 0;

}
