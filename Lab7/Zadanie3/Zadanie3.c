#include<stdio.h>

void zamienWartosci(int* pA, int* pB){

    //int temp = *pB;

    *pB += *pA;
    *pA = *pB - *pA;
    *pB -= *pA;


}

int main(){

    int a = 3;
    int b = 2;

    printf("a:%d b:%d - wartosci przed wywoalaniem funkcji\n", a,b);

    zamienWartosci(&a, &b);

    printf("a:%d b:%d - wartosci po wywoalaniu funkcji\n", a,b);

    return 0;

}
