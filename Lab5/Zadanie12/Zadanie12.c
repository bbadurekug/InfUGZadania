#include<stdio.h>

int przestepny(int r){

    if(r % 4 == 0 && r % 100 != 0){

        return 1;

    }
    else if(r % 400 == 0){

        return 1;

    }
    else{

        return 0;

    }

}

int ile_dni_ma_miesiac(int m, int r){

    if(m == 2){
            if(przestepny(r))
                return 29;
            else
                return 28;
        }
        else if((m<8 && m%2==1) || (m>=8 && m%2==0))
            return 31;
        else
            return 30;

}

int pozostale_dni_do_daty(int d1, int m1, int r1, int d2, int m2, int r2){

    int ileDni = 0;

    for(;d1 < d2; d1++){

        ileDni++;

    }
    for(;(m1+1) <= m2; m1++){

        ileDni += ile_dni_ma_miesiac((m1+1), r1);

    }
    for(;(r1+1) <= r2; r1++){

        if(przestepny(r1))
            ileDni += 366;
        else
            ileDni += 365;

    }


    return ileDni;

}

int main(){

    int d1,m1,r1,d2,m2,r2;

    printf("Podaj pierwsza poprawna date (dzien miesiac rok):\n");
    scanf("%d %d %d", &d1, &m1, &r1);

    printf("Podaj druga poprawna date (dzien miesiac rok):\n");
    scanf("%d %d %d", &d2, &m2, &r2);

    printf("Pozostalo %d dni do drugiej daty.", pozostale_dni_do_daty(d1,m1,r1,d2,m2,r2));

    return 0;

}
