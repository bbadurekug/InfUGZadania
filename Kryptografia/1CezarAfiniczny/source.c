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

    char inputChar = '\0';

    while(inputChar != '\n' && inputChar != EOF){
        
        inputChar = fgetc(plain);
        input[inputSize - 1] = inputChar;
        input = realloc(input, inputSize++ * sizeof(char));
    }
    
    input[inputSize - 1] = '\0';

    printf("%s\n", input);
    
    //czytanie napisu litera po literze zeby mozna bylo dynamicznie dobra dlugosc tekstu
    
    free(input);

}

int main(int argc, char *argv[]){
    
    if(argc != 3){

        fprintf(stderr, "Nie podano zadnej lub zbyt malo opcji. Podaj dwie opcje. Pierwsza -c dla szyfru cezara lub -a dla szyfru afinicznego i druga -e dla szyfrowania, -d dla odszyfrowywania, -k dla kryptoanalizy z kryptogramem lub -j dla kryptoanalizy z tekstem jawnym");
        return 1;

    }

    char type;

    switch(argv[1][1]){

        case 'c':
            
            type = 'c';
            printf("Cezar\n");
            
            break;

        case 'a':
            
            type = 'a';
            printf("Afiniczny\n");

            break;

       default:

            printf("Nie podano poprawnej pierszej opcji. Uzyj -c dla szyfru cezara lub -a dla szyfru afinicznego");
            return 1;

            break;

    }

    switch(argv[2][1]){

        case 'e':

            printf("Szyfrowanie\n");

            szyfrowanie(type);

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

        default:

            printf("Nie podano poprawnej drugiej opcji. Uzyj -e dla szyfrowania, -d dla odszyfrowywania, -k dla kryptoanalizy z kryptogramem lub -j dla kryptoanalizy z tekstem jawnym");
            return 1;

            break;

    }

    return 0;

}
