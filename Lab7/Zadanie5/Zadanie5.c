#include<stdio.h>

void sortujRosnaco(int* pA, int* pB, int* pC){

    while(*pA > *pB || *pB > *pC){

        if(*pA > *pB){

            *pB += *pA;
            *pA = *pB - *pA;
            *pB -= *pA;

        }

        if(*pB > *pC){

            *pC += *pB;
            *pB = *pC - *pB;
            *pC -= *pB;

        }

    }


}

int main(){

    int a = 3, b = 1, c = 2;

    printf("Przed posortowaniem:\na:%d b:%d c:%d\n", a, b, c);

    sortujRosnaco(&a, &b, &c);

    printf("Po posortowaniu:\na:%d b:%d c:%d\n", a, b, c);

    return 0;

}
