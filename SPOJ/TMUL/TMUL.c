#include<stdio.h>
#include<stdlib.h>

void mnozenieStringow(char *string1, int len1, char *string2, int len2){

    char wyniki[len2][len1+2];

    for(int i = 0; i < len2; i++)
        for(int j = 0; j < len1+2; j++)
            wyniki[i][j] = 0;

    int surplus = 0;
    //-48 do liczb

    for(int i = 0; i < len2; i++){

        for(int j = 0; j < len1; j++){

            wyniki[i][j] = surplus;
            surplus = 0;
            wyniki[i][j] += (string1[len1-1-j] - 48) * (string2[len2-1-i] - 48);
            //printf("co mnozy: %d %d\n", string1[len1-1-j] - 48, string2[len2-1-i] - 48);
            if(wyniki[i][j] > 9){

                surplus = wyniki[i][j] / 10;
                wyniki[i][j] %= 10;

            }
            wyniki[i][j] += 48;
            //printf("wynik: %c surplus: %d\n", wyniki[i][j], surplus);

        }

        if(surplus > 0){
            wyniki[i][len1] = surplus + 48;
            wyniki[i][len1+1] = '\0';
        }
        else
            wyniki[i][len1] = '\0';

        //printf("ostateczny wynik: %s\n", wyniki[i]);
        surplus = 0;

    }

    char wynik[len1 + len2 + 2];

    for(int i = 0; i < len1+ len2 + 2; i++)
        wynik[i] = 0;

    surplus = 0;
    int offset = 0;

    for(int i = 0; i < len1 + len2 + 1; i++){

        wynik[i] = surplus;
        surplus = 0;

        offset = 0;

        for(int j = 0; j < len2; j++){

            //printf("dodaje %d do %d j: %d\n", wynik[i], wyniki[j][i-offset] - 48, i-offset);

            if((i-offset >= 0 && i-offset <= len1 + 1) && wyniki[j][i-offset] != 0){
                wynik[i] += (wyniki[j][i-offset] - 48);
            }

            offset++;
        }

        if(wynik[i] > 9){

            surplus = wynik[i] / 10;
            wynik[i] %= 10;

        }
        wynik[i] += 48;
        //printf("wynik: %c surplus: %d\n", wynik[i], surplus);

    }

    if(wynik[len1 + len2] != 48)
        printf("%c%c", wynik[len1 + len2], wynik[len1 + len2 - 1]);
    else if(wynik[len1 + len2] == 48 && wynik[len1 + len2 - 1] != 48)
        printf("%c", wynik[len1 + len2 - 1]);

    for(int i = len1 + len2 - 2; i >= 0; i--)
        printf("%c", wynik[i]);

    printf("\n");

}

int main(){

    int n;
    scanf("%d ", &n);

    char liczba;
    char *input1 = NULL;
    char *input2 = NULL;
    int size1 = 0;
    int size2 = 0;

    for(int i = 0; i < n; i++){

        size1 = 2;

        input1 = malloc(sizeof(char) * size1);

        int i = 0;

        while(liczba != ' '){

            liczba = getc(stdin);

            //printf("liczba: %c\n", liczba);

            input1[i] = liczba;

            i++;

            //printf("string: %s\n", input1);

            if(i == size1){

                size1 *= 2;
                input1 = realloc(input1, sizeof(char) * size1 + 1);

            }

        }

        i--;

        input1[i] = '\0';

        //printf("%s [%d]", input1, i);

        size2 = 2;

        input2 = malloc(sizeof(char) * size2);

        int j = 0;

        while(liczba != '\n'){

            liczba = getc(stdin);

            //printf("liczba: %c\n", liczba);

            input2[j] = liczba;

            j++;

            //printf("string: %s\n", input1);

            if(j == size2){

                size2 *= 2;
                input2 = realloc(input2, sizeof(char) * size2 + 1);

            }

        }

        j--;

        input2[j] = '\0';

        //printf("%s [%d]\n", input2, j);

        if(input1[0] - 48 == 0 || input2[0] - 48 == 0)
            printf("0\n");
        else if(i >= j)
            mnozenieStringow(input1, i, input2, j);
        else
            mnozenieStringow(input2, j, input1, i);


        free(input1);
        free(input2);

    }

    return 0;

}
