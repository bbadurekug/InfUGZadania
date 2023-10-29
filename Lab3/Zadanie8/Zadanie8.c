#include<stdio.h>
#include<stdlib.h>

int Przestepny(rok){

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

int PoprawnaData(dzien, miesiac, rok){


    if(miesiac<13 && miesiac>0){

        if(dzien<=31 && dzien>0){

            if((dzien<=31 && (miesiac<8 && miesiac%2==1) || (miesiac>=8 && miesiac%2==0)) || (dzien<31 && (miesiac<8 && miesiac%2==0) || (miesiac>=8 && miesiac%2==1))){

                if(dzien>=29 && miesiac == 2 && Przestepny(rok) == 0){

                    return 0;

                }
                else if(dzien>28 && miesiac == 2 && Przestepny(rok) == 0){

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



}


int main(){

    int dzien1, miesiac1, rok1, dzien2, miesiac2, rok2, rozdzien, rozmies, rozrok;


    printf("Podaj pierwszą datę: dzień, miesiąć i rok (miesiąc w formie liczby): \n");
    scanf("%d", &dzien1);
    scanf("%d", &miesiac1);
    scanf("%d", &rok1);

    printf("Podaj drugą datę: dzień, miesiąć i rok (miesiąc w formie liczby): \n");
    scanf("%d", &dzien2);
    scanf("%d", &miesiac2);
    scanf("%d", &rok2);

    if(PoprawnaData(dzien1, miesiac1, rok1) == 1 && PoprawnaData(dzien2, miesiac2, rok2) == 1){

        rozdzien = abs(dzien1 - dzien2);
        rozmies = abs(miesiac1 - miesiac2);
        rozrok = abs(rok1 - rok2);

        printf("Te daty różni: \n");
        printf("%d dni \n", rozdzien);
        printf("%d miesiecy \n", rozmies);
        printf("%d lat \n", rozrok);

    }
    else{

        printf("Jedna lub dwie z tych dat są niepoprawne.");

    }

}
