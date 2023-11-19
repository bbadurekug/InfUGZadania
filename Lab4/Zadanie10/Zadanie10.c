#include<stdio.h>
#include<stdlib.h>

int main(){

    int pole[10][10];
    int x1, y1, x2, y2;
    short odbicieX = 0;
    short odbicieY = 0;

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

    while(1){

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

        //obliczanie nastepnego x2, y2

        //jezeli przyszla pozycja pilki wychodzi za granice X i Y, to deltaX i deltaY musza byc obrocone
        //jezeli przyszla pozycja pilki wychodzi za granice X, to deltaX musi byc obrocone
        //jezeli przyszla pozycja pilki wychodzi za granice Y, to deltaY musi byc obrocone

        if((odbicieX%2 == 0) && (odbicieY%2 == 0)){

            if((x2 - deltaX > 10) || (x2 - deltaX < 1)){

                odbicieX++;

            }

            if((y2 - deltaY > 10) || (y2 - deltaY < 1)){

                odbicieY++;

            }

        }

        if(odbicieX){

            x2 += deltaX;
            odbicieX--;

        }
        else{

            x2 -= deltaX;

        }

        if(odbicieY){

            y2 += deltaY;
            odbicieY--;

        }
        else{

            y2 -= deltaY;

        }


        sleep(1);


    }

    return 0;

}
