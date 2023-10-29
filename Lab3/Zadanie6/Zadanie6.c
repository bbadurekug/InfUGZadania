#include<stdio.h>

int main(){

    printf("Podaj rok: \n");

    int rok;

    scanf("%d", &rok);

    if(rok % 4 == 0 && rok % 100 != 0){

        printf("Rok %d jest rokiem przestępnym.", rok);

    }
    else if(rok % 400 == 0){

        printf("Rok %d jest rokiem przestępnym.", rok);

    }
    else{

        printf("Rok %d nie jest rokiem przestępnym.", rok);

    }

}
