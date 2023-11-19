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


int main(){

    int dzien, miesiac, rok;

    printf("Podaj dzień, miesiąć i rok (miesiąc w formie liczby): \n");
    scanf("%d %d %d", &dzien, &miesiac, &rok);

    if(miesiac<13 && miesiac>0){

        if(dzien<=31 && dzien>0){

            if((dzien<=31 && (miesiac<8 && miesiac%2==1) || (miesiac>=8 && miesiac%2==0)) || (dzien<31 && (miesiac<8 && miesiac%2==0) || (miesiac>=8 && miesiac%2==1))){

                if(dzien>=29 && miesiac == 2 && przestepny(rok) == 0){

                    printf("To nie jest poprawna data.");

                }
                else if(dzien>28 && miesiac == 2 && przestepny(rok) == 0){

                    printf("To nie jest poprawna data.");

                }
                else{

                    if(rok>0){

                        printf("To jest poprawna data.");

                    }
                    else{

                        printf("To nie jest poprawna data.");

                    }

                }

            }
            else{

                printf("To nie jest poprawna data.");

            }
        }
        else{

        printf("To nie jest poprawna data.");

        }

    }
    else{

        printf("To nie jest poprawna data.");

    }

    return 0;

}
