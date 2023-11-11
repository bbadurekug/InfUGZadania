#include<stdio.h>

int main(){

    int liczba = 3;
    int proba;

    printf("Zgadnij liczbe od 1 do 5:\n");

    for(int i = 0; i < 3; i++){

        scanf("%d", &proba);

        if(proba <= 5 && proba >= 1){

            if(proba == liczba){

                printf("Zgadles/as!");
                break;

            }
            else
                printf("Zla odpowiedz. Probuj dalej.\n");

        }
        else{

            printf("Ta liczba nie miesci sie w zakresie. Tracisz jedna szanse.\n");

        }

    }

    return 0;

}
