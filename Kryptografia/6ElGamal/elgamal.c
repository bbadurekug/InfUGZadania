//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* subtract(char* num1, char* num2){

    char* number = NULL;

    int numberLen = (strlen(num1) > strlen(num2)) ? strlen(num1) : strlen(num2);

    number = malloc(numberLen * sizeof(char));

    for(int i = 0; i < numberLen; i++){



    }

    return number;

}

char* getLongNumber(FILE* sourceFile){

    char* number = NULL;
    int numberLen = 0;
    number = malloc((numberLen + 1) * sizeof(char));

    char input = getc(sourceFile);

    while(input >= '0' && input <= '9'){

        number = realloc(number, (++numberLen + 1) * sizeof(char));

        number[numberLen - 1] = input - '0';
        number[numberLen] = '\0';

        input = getc(sourceFile);

    }

    //printf("%d\n", numberLen);

    return number;

}

void keys(){

    FILE* elgamal = NULL;
    elgamal = fopen("./elgamal.txt", "r");

    char* number1;
    char* number2;

    number1 = getLongNumber(elgamal);
    number2 = getLongNumber(elgamal);

    printf("%s %ld\n%s %ld\n", number1, strlen(number1) - 1, number2, strlen(number2) - 1);



    free(number1);
    free(number2);
    fclose(elgamal);

}

int main(int argc, char *argv[]){

    if(argc != 2){

        fprintf(stderr, "Nie podano zadnej opcji. Podaj jedna opcje.");
        return 1;

    }

    char type;

    switch(argv[1][1]){

        case 'k':

            printf("Generowanie kluczy\n");
            keys();

            break;

        case 'e':

            printf("Szyfrowanie\n");

            break;

        case 'd':

            printf("Odszyfrowanie\n");

            break;

        case 's':

            printf("Generowanie podpisu\n");

            break;

        case 'v':

            printf("Weryfikacja\n");

            break;

       default:

            printf("Nie podano poprawnej pierszej opcji.");
            return 1;

            break;

    }

    return 0;

}
