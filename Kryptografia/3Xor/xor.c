//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define keyLength   32

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
        else if(input[i] == 32){

            inputPlain = realloc(inputPlain, inputSizePlain++ * sizeof(char));
            inputPlain[inputSizePlain - 2] = input[i];

        }

    }

    inputPlain[inputSizePlain - 1] = '\0';

    FILE *plain = NULL;

    plain = fopen("./plain.txt", "w");

    int newLine = 0;

    for(int i = 0; i < strlen(inputPlain) - 1; i++){

        fputc(inputPlain[i], plain);

        newLine++;

        if(newLine == keyLength){

            fprintf(plain, "\n");
            newLine = 0;

        }

    }

    fclose(orig);
    fclose(plain);

    free(input);
    free(inputPlain);


}

void szyfrowanie(){

    FILE *keyFile = NULL;
    keyFile = fopen("./key.txt", "r");

    char key[keyLength + 1];

    for(int i = 0; i < keyLength; i++){

        key[i] = fgetc(keyFile);

    }

    key[keyLength] = '\0';

    printf("%s\n\n", key);

    FILE *plain = NULL;
    plain = fopen("./plain.txt", "r");

    FILE *crypto = NULL;
    crypto = fopen("./crypto.txt", "w");

    char input[keyLength + 1];
    char inputChar;

    input[keyLength] = '\0';

    int i = 0;

    while(inputChar != EOF){

        inputChar = fgetc(plain);

        if(inputChar == '\n'){

            //printf("%s\n", input);

            for(int j = 0; j < keyLength; j++){

                input[j] ^= key[j];

                //input[j] ^= key[j];

                fprintf(crypto, "%c", input[j]);

            }

            //fprintf(crypto, "%s", input);

            //decryption for testing

            /*for(int j = 0; j < keyLength; j++){

                input[j] ^= key[j];

            }

            printf("%s\n\n", input);*/

            i = 0;

        }
        else{

            input[i++] = inputChar;

        }

    }

    --i;

    if(i != 0){

        for(int j = 0; j < i; j++){

            //printf("%c", input[j]);
            input[j] ^= key[j];

            //input[j] ^= key[j];

        }

        for(int j = 0; j < i; j++){

            fprintf(crypto, "%c", input[j]);

        }

    }

    fclose(plain);
    fclose(keyFile);
    fclose(crypto);

}

void kryptogram(){

    FILE *crypto = NULL;
    crypto = fopen("./crypto.txt", "r");

    FILE *decrypt = NULL;
    decrypt = fopen("./decrypt.txt", "w");

    /*TEST*/

    FILE *keyFile = NULL;
    keyFile = fopen("./key.txt", "r");

    char key[keyLength + 1];

    for(int i = 0; i < keyLength; i++){

        key[i] = fgetc(keyFile);

    }

    key[keyLength] = '\0';

    /*TEST*/

    char input[keyLength + 1];
    char inputChar;

    input[keyLength] = '\0';

    int i = 0;

    while(inputChar != EOF){

        inputChar = fgetc(crypto);

        if(i == keyLength - 1){

            input[i] = inputChar;

            for(int j = 0; j < keyLength; j++){

                input[j] ^= key[j];

                //input[j] ^= key[j];

                fprintf(decrypt, "%c", input[j]);

            }

            fprintf(decrypt, "\n");

            i = 0;

        }
        else{

            input[i++] = inputChar;

        }

    }

    --i;

    if(i != 0){

        for(int j = 0; j < i; j++){

            input[j] ^= key[j];

            //input[j] ^= key[j];

        }

        for(int j = 0; j < i; j++){

            fprintf(decrypt, "%c", input[j]);

        }

    }

    fclose(keyFile);
    fclose(crypto);
    fclose(decrypt);

}

int main(int argc, char* argv[]){


    if(argc != 2){

        fprintf(stderr, "Nie podano poprawnej ilosci opcji. Podaj jedna opcje. -p dla przygotowania tekstu jawnego -e dla szyfrowania lub -k dla kryptoanalizy z kryptogramem");
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

        case 'k':

            printf("Kryptoanaliza w oparciu na kryptogram\n");

            kryptogram();

            break;

        default:

            printf("Nie podano poprawnej drugiej opcji. Uzyj -p dla przygotowania tekstu jawnego -e dla szyfrowania lub -k dla kryptoanalizy z kryptogramem");
            return 1;

            break;

    }

    return 0;

}

