#include<stdio.h>

int ktora_data_wczesniejsza(int d1, int m1, int r1, int d2, int m2, int r2){

    if(r1 < r2)
        return 1;
    else if(r1 > r2)
        return 2;
    else{
         if(m1 < m2)
            return 1;
        else if(m1 > m2)
            return 2;
        else{
             if(d1 < d2)
                return 1;
            else if(d1 > d2)
                return 2;
            else
                return 3;
        }
    }

}

int main(){

    int d1,m1,r1,d2,m2,r2;

    printf("Podaj pierwsza poprawna date (dzien miesiac rok):\n");
    scanf("%d %d %d", &d1, &m1, &r1);

    printf("Podaj druga poprawna date (dzien miesiac rok):\n");
    scanf("%d %d %d", &d2, &m2, &r2);

    if(ktora_data_wczesniejsza(d1,m1,r1,d2,m2,r2) == 1)
        printf("Pierwsza data jest wczesniejsza.");
    else if(ktora_data_wczesniejsza(d1,m1,r1,d2,m2,r2) == 2)
        printf("Druga data jest wczesniejsza.");
    else
        printf("To dwie takie same daty.");

    return 0;

}
