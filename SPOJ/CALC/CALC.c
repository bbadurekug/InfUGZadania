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

    char znak;
    char n[15];

    int i = 0;
    int liczby[2];

    int toArr = 0;

    while(fgets(n, sizeof n, stdin) != NULL) {

        if(n[0] == '\n')
            break;

        if(sscanf(n, "%c %d %d", &znak, &liczby[0], &liczby[1]) == 3){

            switch(znak){

                case '+':
                    printf("%d\n", dodawanie(liczby[0], liczby[1]));
                    break;
                case '-':
                    printf("%d\n", odejmowanie(liczby[0], liczby[1]));
                    break;
                case '*':
                    printf("%d\n", mnozenie(liczby[0], liczby[1]));
                    break;
                case '/':
                    printf("%d\n", dzielenie(liczby[0], liczby[1]));
                    break;
                case '%':
                    printf("%d\n", modulo(liczby[0], liczby[1]));
                    break;

            }

        }
        else
            break;

    }

    return 0;

}
