#include<stdio.h>

int main(){

    int pascal[5][5];

    for(int i1=0; i1 < 5; i1++){               //zeruje miejsca w liscie

        for(int i2=0; i2 < 10; i2++){

            pascal[i1][i2] = 0;

        }

    }

    for(int i = 0; i < 5; i++){                         //wylicza kolejne wartosci dla trojkata


        for(int i1 = 0; i1 <= i; i1++){


            if(i1 == 0){

                pascal[i][i1] = 1;

            }
            else{

                pascal[i][i1] = pascal[i-1][i1 -1] + pascal[i-1][i1];

            }

        }

    }

    for(int i1=0; i1 < 5; i1++){                                //wypisuje na ekranie


        for(int i2=0; i2 < 5; i2++){

            if(i2 == 0){

                for(int i3 = 5-i1; i3 > 0; i3--){       //tutaj dodajemy spacje zeby trojkat sie wyrownal

                    printf(" ");

                }

            }

            if(pascal[i1][i2] != 0)                     //nie chcemy wypisywac 0 na ekranie
                printf("%d ", pascal[i1][i2]);

        }

        printf("\n");
    }


    return 0;

}
