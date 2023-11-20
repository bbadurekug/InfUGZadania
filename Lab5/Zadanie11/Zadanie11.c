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

int pozostale_dni(int d, int m, int r){

    int ileDni = 0;

    for(;d < ile_dni_ma_miesiac(m,r); d++){

        ileDni++;

    }
    for(;(m+1) <= 12; m++){

        ileDni += ile_dni_ma_miesiac((m+1), r);

    }


    return ileDni;

}

int main(){

    int d,m,r;

    printf("Podaj poprawna date (dzien miesiac rok):\n");
    scanf("%d %d %d", &d, &m, &r);

    printf("Pozostalo %d dni do konca roku.", pozostale_dni(d,m,r));

    return 0;

}
