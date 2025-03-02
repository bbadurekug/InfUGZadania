//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void szyfrowanie(){

    FILE *plain = NULL;
    plain = fopen("./plain.txt", "r");

    //zrobic tak zeby string.h wykrywalo dlugosc tekstu

    char* input;
    int inputSize = 1;
    input = malloc(inputSize * sizeof(char));

    //czytanie napisu litera po literze zeby mozna bylo dynamicznie dobra dlugosc tekstu

}

int main(int argc, char *argv[]){

    switch(argv[1][1]){

        case 'c':

            printf("Cezar\n");

            break;

        case 'a':

            printf("Afiniczny\n");

            break;

    }

    switch(argv[2][1]){

        case 'e':

            printf("Szyfrowanie\n");

            szyfrowanie();

            break;

        case 'd':

            printf("Odszyfrowanie\n");

            break;

        case 'k':

            printf("Kryptoanaliza w oparciu na kryptogram\n");

            break;

        case 'j':

            printf("Kryptoanaliza z tekstem jawnym\n");

            break;

    }

    return 0;

}
