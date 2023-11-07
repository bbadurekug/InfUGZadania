#include<stdio.h>
#include<stdlib.h>

int main(){

    int pole[10][10];
    int x1, y1, x2, y2;

    int deltaX, deltaY;

    for(int i1=0; i1 < 10; i1++){               //zeruje miejsca w liscie

        for(int i2=0; i2 < 10; i2++){

            pole[i1][i2] = 0;

        }

    }

    printf("Podaj dwie pary liczb w zakresie od 1 do 10: \n");
    scanf("%d", &x1);
    scanf("%d", &y1);
    scanf("%d", &x2);
    scanf("%d", &y2);

    pole[y1-1][x1-1] = 120;

    do{

        printf("| - - - - - - - - - - |\n");

        for(int i1=0; i1 < 10; i1++){

            printf("| ");

            for(int i2=0; i2 < 10; i2++){

                printf("%c ", pole[i1][i2]);

            }

            printf("|\n");

        }

        printf("| - - - - - - - - - - |\n");            //28-44 wypisywanie na ekranie

        pole[y1-1][x1-1] = 0;
        pole[y2-1][x2-1] = 120;

        deltaX = x1-x2;
        deltaY = y1-y2;

        x1 = x2;
        y1 = y2;

        x2 = x2 - deltaX;
        y2 = y2 - deltaY;


    }while(((x2 <= 11)&&(y2 <= 11)) && ((x2 > -1)&&(y2 > -1)));

    return 0;

}
