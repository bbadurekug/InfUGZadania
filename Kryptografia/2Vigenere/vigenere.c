//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void przygotowanie(){

    FILE *orig = NULL;
    orig = fopen("./orig.txt", "r");

    char* input;
    int inputSize = 1;
    input = malloc(inputSize * sizeof(char));

    char inputChar = '\0';

    while(inputChar != '\n' && inputChar != EOF){

        inputChar = fgetc(orig);
        input = realloc(input, inputSize++ * sizeof(char));
        input[inputSize - 2] = inputChar;

    }

    input[inputSize - 1] = '\0';

    printf("%s", input);

    char* inputPlain;
    int inputSizePlain = 1;
    inputPlain = malloc(inputSizePlain * sizeof(char));

    for(int i = 0; i < strlen(input) - 1; i++){

        if(input[i] >= 97 && input[i] <= 122){

            inputPlain = realloc(inputPlain, inputSizePlain++ * sizeof(char));
            inputPlain[inputSizePlain - 2] = input[i];

        }
        else if(input[i] >= 65 && input[i] <= 90){

            inputPlain = realloc(inputPlain, inputSizePlain++ * sizeof(char));
            inputPlain[inputSizePlain - 2] = input[i] + 32;

        }

    }

    inputPlain[inputSizePlain - 1] = '\0';

    printf("%s\n", inputPlain);

    FILE *plain = NULL;

    plain = fopen("./plain.txt", "w");

    fprintf(plain, "%s\n", inputPlain);

    fclose(orig);
    fclose(plain);

    free(input);
    free(inputPlain);

}

void szyfrowanie(){

    FILE *plain = NULL;
    plain = fopen("./plain.txt", "r");

    char* input;
    int inputSize = 1;
    input = malloc(inputSize * sizeof(char));

    char inputChar = '\0';

    while(inputChar != '\n' && inputChar != EOF){

        inputChar = fgetc(plain);
        input = realloc(input, inputSize++ * sizeof(char));
        input[inputSize - 2] = inputChar;

    }

    input[inputSize - 1] = '\0';

    printf("%s", input);

    FILE *key = NULL;
    key = fopen("./key.txt", "r");

    char* keys;
    int keysSize = 1;
    keys = malloc(keysSize * sizeof(char));

    int index = 0;
    int inputNumber;

    while(fscanf(key, "%d", &inputNumber) == 1){

        keys[index] = inputNumber % 26;
        keys = realloc(keys, ++keysSize * sizeof(char));
        printf("%d ", keys[index++]);

    }

    keys = realloc(keys, --keysSize * sizeof(char));

    printf("\n%d\n", keysSize);

    for(int i = 0; i < strlen(input) - 1; i++){

        input[i] = input[i] + keys[i % keysSize];

    }

    printf("%s", input);

    FILE *crypto = NULL;

    crypto = fopen("./crypto.txt", "w");

    fprintf(crypto, "%s", input);

    fclose(plain);
    fclose(key);
    fclose(crypto);

    free(input);
    free(keys);

}

void odszyfrowanie(){

    FILE *crypto = NULL;
    crypto = fopen("./crypto.txt", "r");

    char* input;
    int inputSize = 1;
    input = malloc(inputSize * sizeof(char));

    char inputChar = '\0';

    while(inputChar != '\n' && inputChar != EOF){

        inputChar = fgetc(crypto);
        input = realloc(input, inputSize++ * sizeof(char));
        input[inputSize - 2] = inputChar;

    }

    input[inputSize - 1] = '\0';

    printf("%s", input);

    FILE *key = NULL;
    key = fopen("./key.txt", "r");

    char* keys;
    int keysSize = 1;
    keys = malloc(keysSize * sizeof(char));

    int index = 0;
    int inputNumber;

    while(fscanf(key, "%d", &inputNumber) == 1){

        keys[index] = inputNumber % 26;
        keys = realloc(keys, ++keysSize * sizeof(char));
        printf("%d ", keys[index++]);

    }

    keys = realloc(keys, --keysSize * sizeof(char));

    printf("\n%d\n", keysSize);

    for(int i = 0; i < strlen(input) - 1; i++){

        input[i] = input[i] - keys[i % keysSize];

    }

    printf("%s", input);

    FILE *decrypt = NULL;

    decrypt = fopen("./decrypt.txt", "w");

    fprintf(decrypt, "%s", input);

    fclose(crypto);
    fclose(key);
    fclose(decrypt);

    free(input);
    free(keys);

}

void kryptogram(){

}

int main(int argc, char* argv[]){


    if(argc != 2){

        fprintf(stderr, "Nie podano poprawnej ilosci opcji. Podaj jedna opcje. -p dla przygotowania tekstu jawnego -e dla szyfrowania, -d dla odszyfrowywania lub -k dla kryptoanalizy z kryptogramem");
        return 1;

    }

    switch(argv[1][1]){

        case 'p':

            printf("Przygotowanie tekstu jawnego\n");

            przygotowanie();

            break;

        case 'e':

            printf("Szyfrowanie\n");

            szyfrowanie();

            break;

        case 'd':

            printf("Odszyfrowanie\n");

            odszyfrowanie();

            break;

        case 'k':

            printf("Kryptoanaliza w oparciu na kryptogram\n");

            kryptogram();

            break;

        default:

            printf("Nie podano poprawnej drugiej opcji. Uzyj -p dla przygotowania tekstu jawnego -e dla szyfrowania, -d dla odszyfrowywania lub -k dla kryptoanalizy z kryptogramem");
            return 1;

            break;

    }

    return 0;

}
