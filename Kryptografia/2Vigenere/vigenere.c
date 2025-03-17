//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int nwd(int a, int b){

    int temp;

    while (a % b != 0){

        temp = b;
        b = a % b;
        a = temp;

    }

    return b;
    //dodac algorytm na nwd

}

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

        //input[i] = input[i] + keys[i % keysSize];

        input[i] = ((input[i] - 97 + keys[i % keysSize]) % 26) + 97;

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

        //input[i] = input[i] - keys[i % keysSize];

        input[i] = (((input[i] - 97 - keys[i % keysSize]) % 26 + 26) % 26) + 97;

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

    //printf("%s", input);

    //szukanie paternow i co ile sie powtarzaja

    int* hitsTable = NULL;
    int hitsSize = 1;
    hitsTable = malloc(hitsSize * sizeof(int));

    int nChars = 4;

    for(int i = 0; i < strlen(input) - nChars - 1; i++){

        char pattern[nChars+2];

        for(int j = 0; j < nChars; j++){

            pattern[j] = input[j + i];

        }

        pattern[nChars + 1] = '\0';

        //printf("%d: %s\n", i, pattern);

        for(int j = i + nChars; j < strlen(input) - 1; j++){

            int hits = 0;

            for(int k = 0; k < nChars; k++){

                //printf("%c %c %d\n", pattern[k], input[j], k);

                if(pattern[k] == input[j]){

                    hits++;
                    j++;

                }
                else{

                    break;

                }

            }

            if(hits == nChars){

                printf("TRAF! %s %d\n", pattern, (j - nChars) - i);

                hitsTable[hitsSize - 1] = (j - nChars) - i;
                hitsTable = realloc(hitsTable, ++hitsSize * sizeof(int));

                break;

            }

        }

    }

    hitsTable = realloc(hitsTable, --hitsSize * sizeof(int));

    //najmniejszy wspolny dzielnik ZLE POWINIEN BYC NAJWIEKSZY WSPOLNY DZIELNIK

    int gcd = nwd(hitsTable[0], hitsTable[1]);

    for(int i = 2; i < hitsSize; i++){

        gcd = nwd(gcd, hitsTable[i]);

    }

    printf("The key length is most likely %d", gcd);

    free(input);
    free(hitsTable);

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
