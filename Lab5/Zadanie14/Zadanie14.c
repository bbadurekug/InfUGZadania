#include<stdio.h>

int przestepny(int rok){

    if(rok % 4 == 0 && rok % 100 != 0){

        return 1;

    }
    else if(rok % 400 == 0){

        return 1;

    }
    else{

        return 0;

    }

}


int czy_poprawna_data(int dzien, int miesiac, int rok){

    if(miesiac<13 && miesiac>0){

        if(dzien<=31 && dzien>0){

            if((dzien<=31 && (miesiac<8 && miesiac%2==1) || (miesiac>=8 && miesiac%2==0)) || (dzien<31 && (miesiac<8 && miesiac%2==0) || (miesiac>=8 && miesiac%2==1))){

                if(dzien>=29 && miesiac == 2 && przestepny(rok) == 0){

                    return 0;

                }
                else if(dzien>28 && miesiac == 2 && przestepny(rok) == 0){

                    return 0;

                }
                else{

                    if(rok>0){

                        return 1;

                    }
                    else{

                        return 0;

                    }

                }

            }
            else{

                return 0;

            }
        }
        else{

        return 0;

        }

    }
    else{

        return 0;

    }

    return 0;

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

    int menu = 0;

    while(menu == 0){
        printf("Podaj pierwsza poprawna date (dzien miesiac rok):\n");
        scanf("%d %d %d", &d1, &m1, &r1);

        printf("Podaj druga poprawna date (dzien miesiac rok):\n");
        scanf("%d %d %d", &d2, &m2, &r2);

        if(czy_poprawna_data(d1,m1,r1) == 0 || czy_poprawna_data(d2,m2,r2) == 0)
            printf("Jedna lub dwie z podatych dat sa niepoprawne. Sprobuj ponownie\n\n");
        else
            menu++;
    }


    if(ktora_data_wczesniejsza(d1,m1,r1,d2,m2,r2) == 1)
        printf("Te daty rozni %d dni.", pozostale_dni_do_daty(d1,m1,r1,d2,m2,r2));
    else if(ktora_data_wczesniejsza(d1,m1,r1,d2,m2,r2) == 2)
        printf("Te daty rozni %d dni.", pozostale_dni_do_daty(d2,m2,r2,d1,m1,r1));
    else
        printf("To dwie takie same daty.");


    return 0;

}
