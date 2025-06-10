//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gmp.h>

int getHexString(FILE* sourceFile, char** numberResult){

    char* number = NULL;
    int numberLen = 0;
    number = malloc((numberLen + 1) * sizeof(char));

    number[numberLen] = '\0';

    char input = getc(sourceFile);

    while(input >= '0' && input <= '9' || input >= 'a' && input <= 'f' || input >= 'A' && input <= 'F'){

        number = realloc(number, (++numberLen + 1) * sizeof(char));

        number[numberLen - 1] = input;
        number[numberLen] = '\0';

        input = getc(sourceFile);

    }

    if(number[0] != '\0'){

        *numberResult = number;
        return 1;

    }
    else{

        *numberResult = NULL;
        return 0;

    }

}

void immerseEndofline(){

    //check if too short

    FILE *cover = NULL;
    cover = fopen("./cover.html", "r");

    char input = 0;
    int coverLen = 0;

    while((input = fgetc(cover)) != EOF){

        if(input == '\n'){

            coverLen++;

        }

    }

    FILE *mess = NULL;
    mess = fopen("./mess.txt", "r");

    char* hexString;
    getHexString(mess, &hexString);
    fclose(mess);

    int messageLen;
    messageLen = strlen(hexString) * 4;

    //printf("cover: %d message: %d\n", coverLen, messageLen);

    if(coverLen < messageLen){

        fprintf(stderr, "Plik cover.html jest zbyt krótki, aby zaszyfrować wiadomość!");
        free(hexString);
        fclose(mess);
        fclose(cover);
        return;

    }

    //immersing begins

    rewind(cover);

    mpz_t message;
    mpz_init(message);
    mpz_set_str(message, hexString, 16);

    free(hexString);

    //gmp_printf("%Zx\n", message);

    size_t bits = mpz_sizeinbase(message, 2);

    //bit by bit

    FILE *watermark = NULL;
    watermark = fopen("./watermark.html", "w");

    for(ssize_t i = bits - 1; i >= 0; --i){

        int bit =  mpz_tstbit(message, i);

        //read until '\n'

        char* line = NULL;
        int lineLen = 0;
        line = malloc((lineLen + 1) * sizeof(char));

        line[lineLen] = '\0';

        char input = getc(cover);

        while(input != '\n'){

            line = realloc(line, (++lineLen + 1) * sizeof(char));

            line[lineLen - 1] = input;
            line[lineLen] = '\0';

            input = getc(cover);

        }

        //replace based on bit

        if(bit == 0){

            lineLen += 1;
            line = realloc(line, (lineLen + 1) * sizeof(char));
            line[lineLen - 1] = '\n';
            line[lineLen] = '\0';

        }
        else if(bit == 1){

            lineLen += 2;
            line = realloc(line, (lineLen + 1) * sizeof(char));
            line[lineLen - 2] = ' ';
            line[lineLen - 1] = '\n';
            line[lineLen] = '\0';

        }

        fprintf(watermark, "%s", line);
        free(line);

        //printf("%d", bit);

    }

    //write rest of cover.html
    //two spaces at end - end of message

    int end = 1;

    for(ssize_t i = coverLen - bits - 1; i >= 0; --i){

        char* line = NULL;
        int lineLen = 0;
        line = malloc((lineLen + 1) * sizeof(char));

        line[lineLen] = '\0';

        char input = getc(cover);

        while(input != '\n'){

            line = realloc(line, (++lineLen + 1) * sizeof(char));

            line[lineLen - 1] = input;
            line[lineLen] = '\0';

            input = getc(cover);

        }

        if(end == 1){

            lineLen += 3;
            line = realloc(line, (lineLen + 1) * sizeof(char));
            line[lineLen - 3] = ' ';
            line[lineLen - 2] = ' ';
            line[lineLen - 1] = '\n';
            line[lineLen] = '\0';
            end = 0;

        }
        else if(end == 0){

            lineLen += 1;
            line = realloc(line, (lineLen + 1) * sizeof(char));
            line[lineLen - 1] = '\n';
            line[lineLen] = '\0';

        }

        fprintf(watermark, "%s", line);

        free(line);

    }

    mpz_clear(message);

    fclose(watermark);
    fclose(cover);

}

void extractEndofline(){

    FILE *watermark = NULL;
    watermark = fopen("./watermark.html", "r");

    char* result = NULL;
    int resultLen = 0;
    result = malloc((resultLen + 1) * sizeof(char));

    result[resultLen] = '\0';

    char* line = NULL;
    int lineLen = 0;
    line = malloc((lineLen + 1) * sizeof(char));

    line[lineLen] = '\0';

    char input = getc(watermark);

    while(input != EOF){

        if(input != '\n'){

            line = realloc(line, (++lineLen + 1) * sizeof(char));
            line[lineLen - 1] = input;
            line[lineLen] = '\0';

        }
        else{

            if(lineLen >= 2 && line[lineLen - 1] == ' ' && line[lineLen - 2] == ' '){

                //end of cipher

                break;

            }
            else if((lineLen == 1 && line[lineLen - 1] == ' ') || (lineLen >= 2 && line[lineLen - 1] == ' ' && line[lineLen - 2] != ' ')){

                //1

                //printf("1");

                result = realloc(result, (++resultLen + 1) * sizeof(char));
                result[resultLen - 1] = '1';
                result[resultLen] = '\0';

            }
            else{

                //0

                //printf("0");

                result = realloc(result, (++resultLen + 1) * sizeof(char));
                result[resultLen - 1] = '0';
                result[resultLen] = '\0';

            }

            lineLen = 0;
            free(line);
            line = malloc((lineLen + 1) * sizeof(char));

        }

        input = getc(watermark);

    }

    if(line != NULL) free(line);
    fclose(watermark);

    mpz_t message;
    mpz_init(message);
    mpz_set_str(message, result, 2);

    free(result);

    char* hexResult;
    hexResult = mpz_get_str(NULL, 16, message);
    mpz_clear(message);

    FILE *detect = NULL;
    detect = fopen("./detect.txt", "w");

    //printf("%s", hexResult);
    fprintf(detect, "%s", hexResult);

    fclose(detect);

}

void immerseBetweenlines(){

    //check if too short

    FILE *cover = NULL;
    cover = fopen("./cover.html", "r");

    char input = 0;
    int coverLen = 0;

    while((input = fgetc(cover)) != EOF){

        if(input == ' '){

            coverLen++;

        }

    }

    rewind(cover);
    int coverLines = 0;

    while((input = fgetc(cover)) != EOF){

        if(input == '\n'){

            coverLines++;

        }

    }

    FILE *mess = NULL;
    mess = fopen("./mess.txt", "r");

    char* hexString;
    getHexString(mess, &hexString);
    fclose(mess);

    int messageLen;
    messageLen = strlen(hexString) * 4;

    //printf("cover: %d message: %d\n", coverLen, messageLen);

    if(coverLen < messageLen){

        fprintf(stderr, "Plik cover.html jest zbyt krótki, aby zaszyfrować wiadomość!");
        free(hexString);
        fclose(mess);
        fclose(cover);
        return;

    }

    //immersing begins

    rewind(cover);

    mpz_t message;
    mpz_init(message);
    mpz_set_str(message, hexString, 16);

    free(hexString);

    //gmp_printf("%Zx\n", message);

    size_t bits = mpz_sizeinbase(message, 2);
    ssize_t i = bits - 1;
    int bit =  mpz_tstbit(message, i);

    //bit by bit

    FILE *watermark = NULL;
    watermark = fopen("./watermark.html", "w");

    char* line = NULL;
    int lineLen = 0;
    line = malloc((lineLen + 1) * sizeof(char));

    line[lineLen] = '\0';

    input = getc(cover);

    int end = 0;

    while(input != EOF){

        line = realloc(line, (++lineLen + 1) * sizeof(char));
        line[lineLen - 1] = input;
        line[lineLen] = '\0';

        if(input == ' '){

            if(end == 0){

                bit = mpz_tstbit(message, i);

                if(bit == 1){

                    line = realloc(line, (++lineLen + 1) * sizeof(char));
                    line[lineLen - 1] = ' ';
                    line[lineLen] = '\0';

                }

                if(i - 1 >= 0){

                    i--;

                }
                else{

                    end = 1;

                }

            }
            else if(end == 1){

                ++lineLen;
                line = realloc(line, (++lineLen + 1) * sizeof(char));
                line[lineLen - 2] = ' ';
                line[lineLen - 1] = ' ';
                line[lineLen] = '\0';

                end = -1;

            }

        }

        input = getc(cover);

    }

    fprintf(watermark, "%s", line);

    free(line);

    mpz_clear(message);

    fclose(watermark);
    fclose(cover);


}

void extractBetweenlines(){

    FILE *watermark = NULL;
    watermark = fopen("./watermark.html", "r");

    char* result = NULL;
    int resultLen = 0;
    result = malloc((resultLen + 1) * sizeof(char));

    result[resultLen] = '\0';

    char* line = NULL;
    int lineLen = 0;
    line = malloc((lineLen + 1) * sizeof(char));

    line[lineLen] = '\0';

    char input = getc(watermark);

    int space = 0;

    while(input != EOF){

        //printf("%c", input);

        line = realloc(line, (++lineLen + 1) * sizeof(char));
        line[lineLen - 1] = input;
        line[lineLen] = '\0';

        if(input == ' ' && space == 0){

            space = 1;

        }

        if(input != ' ' && space == 1){

            if(lineLen >= 4 && line[lineLen - 2] == ' ' && line[lineLen - 3] == ' ' && line[lineLen - 4] == ' '){

                break;

            }
            else if(lineLen >= 3 && line[lineLen - 2] == ' ' && line[lineLen - 3] == ' '){

                //1

                //printf("1");

                result = realloc(result, (++resultLen + 1) * sizeof(char));
                result[resultLen - 1] = '1';
                result[resultLen] = '\0';

            }
            else if(lineLen >= 3 && line[lineLen - 2] == ' ' && line[lineLen - 3] != ' '){

                //0

                //printf("0");

                result = realloc(result, (++resultLen + 1) * sizeof(char));
                result[resultLen - 1] = '0';
                result[resultLen] = '\0';

            }

            space = 0;

        }

        input = getc(watermark);

    }

    if(line != NULL) free(line);
    fclose(watermark);

    mpz_t message;
    mpz_init(message);
    mpz_set_str(message, result, 2);

    free(result);

    char* hexResult;
    hexResult = mpz_get_str(NULL, 16, message);
    mpz_clear(message);

    FILE *detect = NULL;
    detect = fopen("./detect.txt", "w");

    //printf("%s", hexResult);
    fprintf(detect, "%s", hexResult);

    fclose(detect);

}

void immerseAttribute(){

     //check if too short

    FILE *cover = NULL;
    cover = fopen("./cover.html", "r");

    char* coverLine = NULL;
    int coverLineLen = 0;

    coverLine = malloc((coverLineLen + 1) * sizeof(char));

    char input = 0;
    int coverLen = 0;

    while((input = fgetc(cover)) != EOF){

        coverLine = realloc(coverLine, (++coverLineLen + 1) * sizeof(char));
        coverLine[coverLineLen - 1] = input;
        coverLine[coverLineLen] = '\0';

        if(input == '\n'){

            if((strstr(coverLine, "<p ") != NULL && strstr(coverLine, "style=") == NULL) || strstr(coverLine, "<p>") != NULL ){

                coverLen++;

            }

            coverLineLen = 0;
            coverLine = realloc(coverLine, (coverLineLen + 1) * sizeof(char));

        }

    }

    free(coverLine);

    rewind(cover);
    int coverLines = 0;

    while((input = fgetc(cover)) != EOF){

        if(input == '\n'){

            coverLines++;

        }

    }

    FILE *mess = NULL;
    mess = fopen("./mess.txt", "r");

    char* hexString;
    getHexString(mess, &hexString);
    fclose(mess);

    int messageLen;
    messageLen = strlen(hexString) * 4;

    //printf("cover: %d message: %d\n", coverLen, messageLen);

    if(coverLen < messageLen){

        fprintf(stderr, "Plik cover.html jest zbyt krótki, aby zaszyfrować wiadomość!");
        free(hexString);
        fclose(mess);
        fclose(cover);
        return;

    }

    //immersing begins

    rewind(cover);

    mpz_t message;
    mpz_init(message);
    mpz_set_str(message, hexString, 16);

    free(hexString);

    //gmp_printf("%Zx\n", message);

    size_t bits = mpz_sizeinbase(message, 2);
    ssize_t i = bits - 1;

    //bit by bit

    FILE *watermark = NULL;
    watermark = fopen("./watermark.html", "w");

    char* line = NULL;
    int lineLen = 1;
    line = malloc((lineLen + 1) * sizeof(char));

    input = getc(cover);

    line[lineLen - 1] = input;
    line[lineLen] = '\0';

    while((input = fgetc(cover)) != EOF){

        line = realloc(line, (++lineLen + 1) * sizeof(char));
        line[lineLen - 1] = input;
        line[lineLen] = '\0';

        if(input == '\n' && i >= 0){

            if((strstr(line, "<p ") != NULL && strstr(line, "style=") == NULL) || strstr(line, "<p>") != NULL){

                char* newLine = NULL;
                newLine = calloc((lineLen + 49), sizeof(char));

                char* found = strstr(line, ">");

                if(mpz_tstbit(message, i--) == 0){

                    //printf("0");
                    strncpy(newLine, line, found - line);
                    strcat(newLine, " style=\"margin-botom: 0cm; line-height: 100%\">");
                    strcat(newLine, found + 1);

                }
                else{

                    //printf("1");
                    strncpy(newLine, line, found - line);
                    strcat(newLine, " style=\"margin-bottom: 0cm; lineheight: 100%\">");
                    strcat(newLine, found + 1);

                }

                free(line);
                line = malloc((lineLen + 48) * sizeof(char));
                strcpy(line, newLine);
                free(newLine);

            }

            fprintf(watermark, "%s", line);
            lineLen = 0;
            line = realloc(line, (lineLen + 1) * sizeof(char));

        }

    }

    fprintf(watermark, "%s", line);
    free(line);

    mpz_clear(message);

    fclose(watermark);
    fclose(cover);

}

void extractAttribute(){

    FILE *watermark = NULL;
    watermark = fopen("./watermark.html", "r");

    char* result = NULL;
    int resultLen = 0;
    result = malloc((resultLen + 1) * sizeof(char));

    result[resultLen] = '\0';

    char* line = NULL;
    int lineLen = 0;
    line = malloc((lineLen + 1) * sizeof(char));

    line[lineLen] = '\0';

    char input = 0;

    while((input = fgetc(watermark)) != EOF){

        line = realloc(line, (++lineLen + 1) * sizeof(char));
        line[lineLen - 1] = input;
        line[lineLen] = '\0';

        if(input == '\n'){

            if(strstr(line, " style=\"margin-botom: 0cm; line-height: 100%\">") != NULL){

                //printf("0");

                result = realloc(result, (++resultLen + 1) * sizeof(char));
                result[resultLen - 1] = '0';
                result[resultLen] = '\0';

            }
            else if(strstr(line, " style=\"margin-bottom: 0cm; lineheight: 100%\">") != NULL){

                //printf("1");

                result = realloc(result, (++resultLen + 1) * sizeof(char));
                result[resultLen - 1] = '1';
                result[resultLen] = '\0';

            }

            lineLen = 0;
            line = realloc(line, (lineLen + 1) * sizeof(char));

        }

    }

    if(line != NULL) free(line);
    fclose(watermark);

    mpz_t message;
    mpz_init(message);
    mpz_set_str(message, result, 2);

    free(result);

    char* hexResult;
    hexResult = mpz_get_str(NULL, 16, message);
    mpz_clear(message);

    FILE *detect = NULL;
    detect = fopen("./detect.txt", "w");

    //printf("%s", hexResult);
    fprintf(detect, "%s", hexResult);

    fclose(detect);

}

void immerseTag(){

}

void extractTag(){

}

int main(int argc, char *argv[]){

    if(argc < 2 || argc > 3){

        fprintf(stderr, "Podano niepoprawną ilość opcji!");
        return 1;

    }

    switch(argv[1][1]){

        case 'e':

            printf("Zanurzanie\n");

            switch(argv[2][1]){

                case '1':

                    printf("Spacja na końcu wiersza\n");

                    immerseEndofline();

                    break;

                case '2':

                    printf("Spacja między wierszami\n");

                    immerseBetweenlines();

                    break;

                case '3':

                    printf("Literówki w atrybutach\n");

                    immerseAttribute();

                    break;

                case '4':

                    printf("Niepotrzebne znaczniki\n");

                    immerseTag();

                    break;

                default:

                    printf("Nie podano poprawnej drugiej opcji. Uzyj -1 dla spacji na końcu wiersza, -2 dla spacji między wierszami, -3 dla literówek w atrybutach lub -4 dla niepotrzebnych znaczników");
                    return 1;

                    break;

            }

            break;

        case 'd':

            printf("Wyodrębnianie\n");

            switch(argv[2][1]){

                case '1':

                    printf("Spacja na końcu wiersza\n");

                    extractEndofline();

                    break;

                case '2':

                    printf("Spacja między wierszami\n");

                    extractBetweenlines();

                    break;

                case '3':

                    printf("Literówki w atrybutach\n");

                    extractAttribute();

                    break;

                case '4':

                    printf("Niepotrzebne znaczniki\n");

                    extractTag();

                    break;

                default:

                    printf("Nie podano poprawnej drugiej opcji. Uzyj -1 dla spacji na końcu wiersza, -2 dla spacji między wierszami, -3 dla literówek w atrybutach lub -4 dla niepotrzebnych znaczników");
                    return 1;

                    break;

            }

            break;

       default:

            printf("Nie podano poprawnej pierszej opcji. Uzyj -e dla zanurzania lub -d dla wyodrębniania");
            return 1;

            break;

    }

    return 0;

}
