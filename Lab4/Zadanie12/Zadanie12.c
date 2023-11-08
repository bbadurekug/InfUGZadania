#include<stdio.h>
#include<math.h>

int dlugoscInta(int x){

    int l;

    l = log10(x) + 1;

    return l;

}

int main(){

    int n;

    printf("Podaj wysokosc trojkata Pascala: \n");
    scanf("%d", &n);

    int pascal[n][n];

    for(int i1=0; i1 < n; i1++){               //zeruje miejsca w liscie

        for(int i2=0; i2 < n; i2++){

            pascal[i1][i2] = 0;

        }

    }

    for(int i = 0; i < n; i++){                         //wylicza kolejne wartosci dla trojkata


        for(int i1 = 0; i1 <= i; i1++){


            if(i1 == 0){

                pascal[i][i1] = 1;

            }
            else{

                pascal[i][i1] = pascal[i-1][i1 -1] + pascal[i-1][i1];

            }

        }

    }

    for(int i1=0; i1 < n; i1++){                                //wypisuje na ekranie


        for(int i2=0; i2 < n; i2++){

            if(i2 == 0){

                for(int i3 = ((dlugoscInta(pascal[n-1][n/2]) * (n-1)) - (i1 * dlugoscInta(pascal[n-1][n/2])))/2; i3 > 0; i3--){       //tutaj dodajemy spacje zeby trojkat sie wyrownal

                    printf(" ");

                }

            }

            if(pascal[i1][i2] != 0){                     //nie chcemy wypisywac 0 na ekranie

                printf("%d ", pascal[i1][i2]);

                for(int i4 = 1; i4 < dlugoscInta(pascal[n-1][n/2]) - dlugoscInta(pascal[i1][i2]); i4++){

                    printf(" ");

                }

            }
        }

        printf("\n");
    }


    return 0;

}

//mozna minimalnie zoptymalizowac ilosc spacji i ich rozmieszczenie

//maksymalny n ktory pokazuje bez przechodzenia na nastepna linie to 29
