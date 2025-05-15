//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"tommath/tommath.h"

/*char* add(char* num1, char* num2){

    char* number = NULL;
    char* longerNum = NULL;
    char* shorterNum = NULL;
    int num1Len = strlen(num1);
    int num2Len = strlen(num2);

    int carry = 0;
    int numberLen = 0;
    int shorterLen = 0;

    if(num1Len > num2Len){

        numberLen = num1Len;
        shorterLen = num2Len;
        longerNum = malloc((numberLen + 1) * sizeof(char));
        shorterNum = malloc((shorterLen + 1) * sizeof(char));
        strcpy(longerNum, num1);
        strcpy(shorterNum, num2);

    }
    else{

        numberLen = num2Len;
        shorterLen = num1Len;
        longerNum = malloc((numberLen + 1) * sizeof(char));
        shorterNum = malloc((shorterLen + 1) * sizeof(char));
        strcpy(longerNum, num2);
        strcpy(shorterNum, num1);

    }

    number = malloc((numberLen + 1) * sizeof(char));

    number[numberLen] = '\0';

    for(int i = 1; i <= shorterLen; i++){

        number[numberLen - i] = (longerNum[numberLen - i] - '0') + (shorterNum[shorterLen - i] - '0') + carry;

        if(number[numberLen - i] > 9){

            carry = number[numberLen - i] / 10;
            number[numberLen - i] %= 10;

        }
        else{

            carry = 0;

        }

        number[numberLen - i] += '0';

    }

    for(int i = shorterLen + 1; i <= numberLen; i++){

        number[numberLen - i] = (longerNum[numberLen - i] - '0') + carry;

        if(number[numberLen - i] > 9){

            carry = number[numberLen - i] / 10;
            number[numberLen - i] %= 10;

        }
        else{

            carry = 0;

        }

        number[numberLen - i] += '0';

    }

    free(longerNum);
    free(shorterNum);

    return number;

}*/

char* getLongNumber(FILE* sourceFile){

    char* number = NULL;
    int numberLen = 0;
    number = malloc((numberLen + 1) * sizeof(char));

    char input = getc(sourceFile);

    while(input >= '0' && input <= '9'){

        number = realloc(number, (++numberLen + 1) * sizeof(char));

        number[numberLen - 1] = input;
        number[numberLen] = '\0';

        input = getc(sourceFile);

    }

    //printf("%d\n", numberLen);

    return number;

}

void keys(){

    FILE* elgamal = NULL;
    elgamal = fopen("./elgamal.txt", "r");

    char* num1 = NULL;
    char* num2 = NULL;

    num1 = getLongNumber(elgamal);
    num2 = getLongNumber(elgamal);

    mp_int p, g, random, result;

    mp_init(&p);
    mp_init(&g);
    mp_init(&random);
    mp_init(&result);

    mp_read_radix(&p, num1, 10);
    mp_read_radix(&g, num2, 10);

    free(num1);
    free(num2);

    srand(time(NULL));
    mp_rand(&random, 128);

    mp_int mod;
    mp_init(&mod);

    mp_read_radix(&mod, "10", 10);
    mp_expt_n(&mod, 90, &mod);

    mp_mod(&random, &mod, &random);

    char private_key[256];
    mp_to_radix(&random, private_key, 256, NULL, 10);

    mp_exptmod(&g, &random, &p, &result);

    char public_key[256];
    mp_to_radix(&result, public_key, 256, NULL, 10);

    printf("Private:\n%s\nPublic:\n%s\n", private_key, public_key);

    mp_clear_multi(&p, &g, &random, &result, NULL);

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
