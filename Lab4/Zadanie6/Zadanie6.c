#include<stdio.h>

int main(){

    int kolumny,rzedy;
    int wartosc_kolumna, wartosc_rzad;

    printf("Podaj ilosc rzedow w tablicy dwuwymiarowej: \n");
    scanf("%d", &rzedy);
    printf("Podaj ilosc kolumn w tablicy dwuwymiarowej: \n");
    scanf("%d", &kolumny);

    int tablica[rzedy][kolumny];

    for(int i0 = 0; i0 < rzedy ; i0++){

        for(int i1 = 0; i1 < kolumny ; i1++){

            printf("Podaj wartość 0 lub 1 dla: i[%d][%d]", i0, i1);
            scanf("%d", &wartosc_rzad);
            scanf("%d", &wartosc_kolumna);
            //tablica[i0][i1] = {wartosc_rzad, wartosc_kolumna};

        }

    }


    for(int i0 = 0; i0 < rzedy ; i0++){

        for(int i1 = 0; i1 < kolumny ; i1++){

            printf("%d", tablica[i0][i1]);

        }

    }

    return 0;

}
