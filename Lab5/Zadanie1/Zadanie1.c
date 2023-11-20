#include<stdio.h>

float dodawnie(float a, float b){

    return a + b;

}

float odejmowanie(float a, float b){

    return a - b;

}

float mnozenie(float a, float b){

    return a * b;

}

float dzielenie(float a, float b){

    return a / b;

}

int main(){

    unsigned int menu = 0;

    float a,b;

    printf("Podaj dwie liczby (oddzielone spacja):\n");
    scanf("%f %f", &a, &b);
    printf("Wybierz dzialanie: 1-dodawanie, 2-odejmowanie, 3-mnozenie, 4-dzielenie\n");


    while(menu > 4 || menu < 1){
        scanf("%d", &menu);
        switch(menu){
            case 1:
                printf("Wynik dodawania %f i %f to %f\n", a, b, dodawnie(a,b));
                break;
            case 2:
                printf("Wynik odejmowania %f i %f to %f\n",a, b,odejmowanie(a,b));
                break;
            case 3:
                printf("Wynik mnozenia %f i %f to %f\n",a, b,mnozenie(a,b));
                break;
            case 4:
                printf("Wynik dzielenia %f i %f to %f\n",a, b,dzielenie(a,b));
                break;
            default:
                printf("Nie ma takiej opcji. Sprobuj ponownie:\n");
                break;
        }
    }

    return 0;

}
