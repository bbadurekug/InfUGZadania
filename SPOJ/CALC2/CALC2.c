#include<stdio.h>

int dodawanie(int a, int b){

    return a+b;

}

int odejmowanie(int a, int b){

    return a-b;

}

int mnozenie(int a, int b){

    return a*b;

}

int dzielenie(int a, int b){

    return a/b;

}

int modulo(int a, int b){

    return a%b;

}

int main(){

    char n[15];

    char znak;
    int i = 0;
    int liczba = 0;
    int pamiec[10] = {0};

    while(fgets(n, sizeof n, stdin) != NULL) {

        if(n[0] == '\n')
            break;

        if(sscanf(n, "%c %d %d", &znak, &i, &liczba) == 3){

            switch(znak){

                case 'z':
                    pamiec[i] = liczba;
                    break;
                case '+':
                    printf("%d\n", dodawanie(pamiec[i], pamiec[liczba]));
                    break;
                case '-':
                    printf("%d\n", odejmowanie(pamiec[i], pamiec[liczba]));
                    break;
                case '*':
                    printf("%d\n", mnozenie(pamiec[i], pamiec[liczba]));
                    break;
                case '/':
                    printf("%d\n", dzielenie(pamiec[i], pamiec[liczba]));
                    break;
                case '%':
                    printf("%d\n", modulo(pamiec[i], pamiec[liczba]));
                    break;

            }

        }
        else
            break;

    }

    return 0;

}
