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

int stringCompare(char* longer, char* shorter){

    for(int i = 0; i < strlen(shorter) - 1; i++){

        if(longer[i] != shorter[i]) return 0;

    }

    return 1;

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

        if(nwd(26, factor) != 1){

            fprintf(stderr, "Niepoprawny klucz! NWD(26,a) nie jest rowny 1!");
            return;

        }

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

        //printf("%d %d %d\n", factor, offset, nwd(26, factor));

        if(nwd(26, factor) != 1){

            fprintf(stderr, "Niepoprawny klucz! NWD(26,a) nie jest rowny 1!");
            return;

        }

        int revFactor = -1;

        for(int i = 0; i < 26; i++){

            if(revFactor == -1 && (factor * i) % 26 == 1){

                revFactor = i;

            }
            else if(revFactor != -1 && (factor * i) % 26 == 1){

                fprintf(stderr, "Istnieje wiele odwrotnych liczb!");
                free(input);
                return;

            }

        }

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

void kryptogram(char type){

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

    FILE *decrypt = NULL;

    decrypt = fopen("./decrypt.txt", "w");

    char* inputCopy;
    inputCopy = malloc(strlen(input) + 1);

    if(type == 'a'){

        int dividers[] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

        strcpy(inputCopy, input);

        for(int i = 0; i < 12; i++){

            for(int offset = 0; offset < 26; offset++){

                if(i == 0 && offset == 0) offset = 1;

                for(int j = 0; j < strlen(input) - 1; j++){

                    if(inputCopy[j] >= 65 && inputCopy[j] <= 90){

                        inputCopy[j] = ((((inputCopy[j] - 65 - offset) * dividers[i]) % 26 + 26) % 26) + 65;

                    }
                    else if(inputCopy[j] >= 97 && inputCopy[j] <= 122){

                        inputCopy[j] = ((((inputCopy[j] - 97 - offset) * dividers[i]) % 26 + 26) % 26) + 97;

                    }

                }

                fprintf(decrypt, "%s", inputCopy);
                printf("%s", inputCopy);
                strcpy(inputCopy, input);

            }

        }

    }
    else{

        for(int offset = 1; offset < 26; offset++){

            for(int i = 0; i < strlen(input) - 1; i++){

                if(input[i] >= 65 && input[i] <= 90){

                    input[i] = (((input[i] - 65 - 1) % 26 + 26) % 26) + 65;

                }
                else if(input[i] >= 97 && input[i] <= 122){

                    input[i] = (((input[i] - 97 - 1) % 26 + 26) % 26) + 97;

                }

            }

            fprintf(decrypt, "%s", input);
            //printf("%s", input);

        }

    }

    decrypt = NULL;
    crypto = NULL;

    free(inputCopy);
    free(input);

}

void jawny(char type){

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

    FILE *extra = NULL;

    extra = fopen("./extra.txt", "r");

    char* inputExtra;
    int inputExtraSize = 1;
    inputExtra = malloc(inputExtraSize * sizeof(char));

    inputChar = '\0';

    while(inputChar != '\n' && inputChar != EOF){

        inputChar = fgetc(extra);
        inputExtra[inputExtraSize - 1] = inputChar;
        inputExtra = realloc(inputExtra, inputExtraSize++ * sizeof(char));

    }

    inputExtra[inputExtraSize - 1] = '\0';

    //printf("%s%s", input, inputExtra);

    char* inputCopy;
    inputCopy = malloc(strlen(input) + 1);

    char* inputMatch;
    inputMatch = malloc(strlen(input) + 1);

    int offsetFound = -1;
    int revFactor = -1;
    int factorFound = -1;

    if(type == 'a'){

        int dividers[] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

        strcpy(inputCopy, input);

        for(int i = 0; i < 12; i++){

            for(int offset = 0; offset < 26; offset++){

                if(i == 0 && offset == 0) offset = 1;

                for(int j = 0; j < strlen(input) - 1; j++){

                    if(inputCopy[j] >= 65 && inputCopy[j] <= 90){

                        inputCopy[j] = ((((inputCopy[j] - 65 - offset) * dividers[i]) % 26 + 26) % 26) + 65;

                    }
                    else if(inputCopy[j] >= 97 && inputCopy[j] <= 122){

                        inputCopy[j] = ((((inputCopy[j] - 97 - offset) * dividers[i]) % 26 + 26) % 26) + 97;

                    }

                }

                if(stringCompare(inputCopy, inputExtra)){

                    //printf("%d ", offset);

                    if(offsetFound == -1 && factorFound == -1){

                        offsetFound = offset;

                        revFactor = dividers[i];

                        for(int i = 0; i < 26; i++){

                            if(factorFound == -1 && (revFactor * i) % 26 == 1){

                                factorFound = i;

                            }
                            else if(factorFound != -1 && (revFactor * i) % 26 == 1){

                                fprintf(stderr, "Istnieje wiele odwrotnych liczb!");
                                free(inputMatch);
                                free(inputCopy);
                                free(input);
                                return;

                            }

                        }

                        strcpy(inputMatch, inputCopy);

                    }
                    else{

                        fprintf(stderr, "Nie mozna zalezc klucza!");

                        free(inputMatch);
                        free(inputCopy);
                        free(input);

                        return;

                    }

                }

                strcpy(inputCopy, input);

            }

        }

        if(offsetFound == -1 && factorFound == -1){

            fprintf(stderr, "Nie mozna zalezc klucza!");

            free(inputMatch);
            free(inputCopy);
            free(input);

            return;

        }

    }
    else{

        strcpy(inputCopy, input);

        for(int offset = 1; offset < 26; offset++){

            for(int i = 0; i < strlen(input) - 1; i++){

                if(inputCopy[i] >= 65 && inputCopy[i] <= 90){

                    inputCopy[i] = (((inputCopy[i] - 65 - offset) % 26 + 26) % 26) + 65;

                }
                else if(inputCopy[i] >= 97 && inputCopy[i] <= 122){

                    inputCopy[i] = (((inputCopy[i] - 97 - offset) % 26 + 26) % 26) + 97;

                }

            }

            //printf("%s%s---------------\n", inputCopy, inputExtra);

            if(stringCompare(inputCopy, inputExtra)){

                //printf("%d ", offset);

                if(offsetFound == -1){

                    offsetFound = offset;
                    strcpy(inputMatch, inputCopy);

                }
                else{

                    fprintf(stderr, "Nie mozna zalezc klucza!");

                    free(inputMatch);
                    free(inputCopy);
                    free(input);

                    return;

                }

            }

            strcpy(inputCopy, input);

        }

        if(offsetFound == -1){

            fprintf(stderr, "Nie mozna zalezc klucza!");

            free(inputMatch);
            free(inputCopy);
            free(input);

            return;

        }

    }

    FILE *keyFound = NULL;
    keyFound = fopen("./key-found.txt", "w");

    fprintf(keyFound, "%d", offsetFound);

    if(type == 'a') fprintf(keyFound, " %d", factorFound);

    FILE *decrypt = NULL;
    decrypt = fopen("./decrypt.txt", "w");
    fprintf(decrypt, "%s", inputMatch);

    decrypt = NULL;
    keyFound = NULL;
    crypto = NULL;
    extra = NULL;

    free(inputMatch);
    free(inputCopy);
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

            kryptogram(type);

            break;

        case 'j':

            printf("Kryptoanaliza z tekstem jawnym\n");

            jawny(type);

            break;

        default:

            printf("Nie podano poprawnej drugiej opcji. Uzyj -e dla szyfrowania, -d dla odszyfrowywania, -k dla kryptoanalizy z kryptogramem lub -j dla kryptoanalizy z tekstem jawnym");
            return 1;

            break;

    }

    return 0;

}
