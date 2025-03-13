//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int nwd(int a, int b){

    //dodac algorytm na nwd

}

void szyfrowanie(char type){

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

    //printf("%s", input);

    FILE *key = NULL;
    key = fopen("./key.txt", "r");

    int offset = 0;
    int factor = 0;

    fscanf(key, "%d", &offset);

    if(type == 'a'){

        fscanf(key, "%d", &factor);

        //printf("%d %d\n", factor, offset);

        for(int i = 0; i < strlen(input) - 1; i++){

            if(input[i] >= 65 && input[i] <= 90){

                input[i] = (((input[i] - 65) * factor + offset) % 26) + 65;

            }
            else if(input[i] >= 97 && input[i] <= 122){

                input[i] = (((input[i] - 97) * factor + offset) % 26) + 97;

            }

        }

    }
    else{

        for(int i = 0; i < strlen(input) - 1; i++){

            if(input[i] >= 65 && input[i] <= 90){

                input[i] = ((input[i] - 65 + offset) % 26) + 65;

            }
            else if(input[i] >= 97 && input[i] <= 122){

                input[i] = ((input[i] - 97 + offset) % 26) + 97;

            }

        }

    }

    //printf("%s", input);

    //czytanie napisu litera po literze zeby mozna bylo dynamicznie dobra dlugosc tekstu

    FILE *crypto = NULL;

    crypto = fopen("./crypto.txt", "w");

    fprintf(crypto, "%s", input);

    plain = NULL;
    key = NULL;
    crypto = NULL;

    free(input);

}

void odszyfrowanie(char type){

    FILE *crypto = NULL;
    crypto = fopen("./crypto.txt", "r");

    //zrobic tak zeby string.h wykrywalo dlugosc tekstu

    char* input;
    int inputSize = 1;
    input = malloc(inputSize * sizeof(char));

    char inputChar = '\0';

    while(inputChar != '\n' && inputChar != EOF){

        inputChar = fgetc(crypto);
        input[inputSize - 1] = inputChar;
        input = realloc(input, inputSize++ * sizeof(char));

    }

    input[inputSize - 1] = '\0';

    //printf("%s", input);

    FILE *key = NULL;
    key = fopen("./key.txt", "r");

    int offset = 0;
    int factor = 0;

    fscanf(key, "%d", &offset);

    if(type == 'a'){

        fscanf(key, "%d", &factor);

        //to check if the key is correct

        //printf("%d %d\n", factor, offset);

        int revFactor = 0;

        for(int i = 0; i < strlen(input) - 1; i++){

            if(input[i] >= 65 && input[i] <= 90){

                input[i] = ((((input[i] - 65 - offset) * revFactor) % 26 + 26) % 26) + 65;

            }
            else if(input[i] >= 97 && input[i] <= 122){

                input[i] = ((((input[i] - 97 - offset) * revFactor) % 26 + 26) % 26) + 97;

            }

        }

    }
    else{

        for(int i = 0; i < strlen(input) - 1; i++){

            if(input[i] >= 65 && input[i] <= 90){

                input[i] = (((input[i] - 65 - offset) % 26 + 26) % 26) + 65;

            }
            else if(input[i] >= 97 && input[i] <= 122){

                input[i] = (((input[i] - 97 - offset) % 26 + 26) % 26) + 97;

            }

        }

    }

    //printf("%s", input);

    //czytanie napisu litera po literze zeby mozna bylo dynamicznie dobra dlugosc tekstu

    FILE *decrypt = NULL;

    decrypt = fopen("./decrypt.txt", "w");

    fprintf(decrypt, "%s", input);

    decrypt = NULL;
    key = NULL;
    crypto = NULL;

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

            odszyfrowanie(type);

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
