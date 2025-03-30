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

    inputPlain[inputSizePlain] = '\0';

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

    //printf("%s\n\n", key);

    FILE *plain = NULL;
    plain = fopen("./plain.txt", "r");

    FILE *crypto = NULL;
    crypto = fopen("./crypto.txt", "wb");

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

void copyArrays(char* destination, char* source, int length){

    for(int i = 0; i < length; i++){

        destination[i] = source[i];

    }

}

void kryptogram(){

    FILE *crypto = NULL;
    crypto = fopen("./crypto.txt", "rb");

    FILE *decrypt = NULL;
    decrypt = fopen("./decrypt.txt", "w");

    FILE *keyFound = NULL;
    keyFound = fopen("./key-found.txt", "w");

    char** inputArray;
    int inputArraySize = 1;
    inputArray = malloc(inputArraySize * sizeof(char*));

    char input[keyLength];
    char inputChar = '\0';

    int i = 0;

    while(inputChar != EOF){

        //printf("hello");

        inputChar = fgetc(crypto);

        if(i == (keyLength - 1)){

            input[i] = inputChar;

            inputArray[inputArraySize - 1] = malloc(keyLength * sizeof(char));
            copyArrays(inputArray[inputArraySize - 1], input, keyLength);

            inputArray = realloc(inputArray, ++inputArraySize * sizeof(char*));

            /*for(int j = 0; j < keyLength; j++){

                inputArray[inputArraySize - 2][j] ^= key[j];

                fprintf(decrypt, "%c", inputArray[inputArraySize - 2][j]);

            }

            fprintf(decrypt, "\n");*/

            i = 0;

        }
        else{

            input[i++] = inputChar;

        }

    }

    --i;

    if(i > 0){

        inputArray[inputArraySize - 1] = malloc(keyLength * sizeof(char));
        copyArrays(inputArray[inputArraySize - 1], input, i);

        /*for(int j = 0; j < i; j++){

            inputArray[inputArraySize - 1][j] ^= key[j];
            fprintf(decrypt, "%c", inputArray[inputArraySize - 1][j]);

        }*/

    }
    else{

        inputArraySize--;

    }

    if(inputArraySize < 3){

        fprintf(stderr, "Tekst zbyt krótki, aby odszyfrować");

    }

    int spaceIndex = -1;
    char key[keyLength];

    for(int j = 0; j < keyLength; j++){

        key[j] = '\0';

    }

    for(int j = 0; j < keyLength; j++){

        for(int k = 0; k < inputArraySize - 1; k++){

            if((inputArray[k][j] ^ inputArray[(k + 1) % inputArraySize][j]) / 64 == 1) {

                //printf("SPACJA %d %d albo %d %d: %c\n", k, j, k + 1, j, inputArray[k][j] ^ key[j]);

                if((inputArray[(k + 1) % inputArraySize][j] ^ inputArray[(k + 2) % inputArraySize][j]) / 64 == 1) {

                    //k + 1 jest spacja albo k i k + 2 sa spacja bo z k + 2 tez wychodzi 1

                    if((inputArray[k][j] ^ inputArray[(k + 2) % inputArraySize][j]) == 0) {

                        //k i k+2 to to samo, wiec nie mozna stwierdzic

                        //printf("SPACJA niezdecyowana\n");

                        spaceIndex = -1;

                    }
                    else{

                        //k i k+2 sa rozne wiec k+1 to spacja

                        //printf("SPACJA to %d %d\n", j, k + 1);

                        spaceIndex = k + 1;

                    }

                }
                else if((inputArray[(k + 1) % inputArraySize][j] ^ inputArray[(k + 2) % inputArraySize][j]) == 0){

                    //spacja dwa razy pod rzad

                    spaceIndex = -1;

                }
                else {

                    //k jest spacja bo k + 1 i k + 2 nie daja 1

                    //printf("SPACJA to %d %d\n", j, k);

                    spaceIndex = k;

                }

                if(spaceIndex != -1){

                    //if(k < inputArraySize - 3) k++;

                    key[j] = inputArray[spaceIndex][j] ^ (1 << 5);

                    //printf("klucz dla %d to %c\n", j, key[j]);

                    spaceIndex = -1;

                    break;

                }

            }

        }

    }

    for(int j = 0; j < keyLength; j++){

        if(key[j] == '\0'){

            //printf("_");
            fprintf(keyFound, "_");

        }
        else{

            //printf("%c", key[j]);
            fprintf(keyFound, "%c", key[j]);

        }

    }

    for(int j = 0; j < inputArraySize - 1; j++){

        for(int k = 0; k < keyLength; k++){

            if(key[k] == '\0'){

                inputArray[j][k] = '_';

            }
            else{

                inputArray[j][k] ^= key[k];

            }

            fprintf(decrypt, "%c", inputArray[j][k]);

        }

        fprintf(decrypt, "\n");

    }

    for(int k = 0; k < i; k++){

        if(key[k] == '\0'){

            inputArray[inputArraySize - 1][k] = '_';

        }
        else{

            inputArray[inputArraySize - 1][k] ^= key[k];

        }

        fprintf(decrypt, "%c", inputArray[inputArraySize - 1][k]);

    }

    fclose(keyFound);
    fclose(crypto);
    fclose(decrypt);

    for(int j = 0; j < inputArraySize; j++){

        free(inputArray[j]);

    }

    free(inputArray);

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

