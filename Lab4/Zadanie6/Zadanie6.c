#include<stdio.h>

int main(){

    int kolumny,rzedy;
    int wartosc_kolumna, wartosc_rzad, wartosc;

    printf("Podaj ilosc rzedow w tablicy dwuwymiarowej: \n");
    scanf("%d", &rzedy);
    printf("Podaj ilosc kolumn w tablicy dwuwymiarowej: \n");
    scanf("%d", &kolumny);

    int tablica[rzedy][kolumny];

    for(int i0 = 0; i0 < rzedy ; i0++){

        for(int i1 = 0; i1 < kolumny ; i1++){

            printf("Podaj wartosc 0 lub 1 dla: i[%d][%d]", i0, i1);
            scanf("%d", &wartosc);
            if(wartosc){

                wartosc = 120;
                tablica[i0][i1] = wartosc;

            }
            else{

                tablica[i0][i1] = wartosc;

            }

        }

    }

    printf("| ");

    for(int i1 = 0; i1 < kolumny ; i1++){

        printf("- ");

    }

    printf("|\n");


    for(int i0 = 0; i0 < rzedy ; i0++){

        printf("| ");

        for(int i1 = 0; i1 < kolumny ; i1++){

            printf("%c ", tablica[i0][i1]);

        }

        printf("|\n");

    }

    printf("| ");

    for(int i1 = 0; i1 < kolumny ; i1++){

        printf("- ");

    }

    printf("|\n");

    return 0;

}
