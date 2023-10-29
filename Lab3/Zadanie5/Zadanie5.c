#include<stdio.h>

int main(){

    int wybor;
    int kod;

    printf("Wpisz 1 dla znaku lub 2 dla kodu ASCII: \n");
    scanf("%d", &wybor);

    if(wybor==1){

        char znak;
        printf("Podaj znak: \n");
        scanf(" %c", &znak);

        if(znak>64 && znak<123){

            printf("%c jest literą alfabetu.", znak);

        }

        else{

            printf("%c nie jest literą alfabetu.", znak);

        }
    }

    else if(wybor==2){


        printf("Podaj kod: \n");
        scanf( "%d", &kod);

        if(kod>64 && kod<123){

            printf("%d jest kodem litery alfabetu.", kod);

        }

        else{

            printf("%d nie jest kodem litery alfabetu.", kod);

        }



    }


}
