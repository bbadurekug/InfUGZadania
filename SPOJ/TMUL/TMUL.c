#include<stdio.h>
#include<stdlib.h>

char* dodawanieStringow(char *string1, int len1, char *string2, int len2){

    char* wynik = malloc(sizeof(char) * (len1 + 2));

    for(int i = 0; i < len1 + 2; i++)
        wynik[i] = 0;

    short surplus = 0;

    for(int i = 0; i < len1 + 1; i++){

        wynik[i] = surplus;
        surplus = 0;

            if((wyniki[j][i] != 0){
                //printf("do %d dodaje %d\n", wynik[i], wyniki[j][i] - 48,);
                wynik[i] += wyniki[j][i] - 48;

                if(wynik[i] > 9){

                    surplus += wynik[i] / 10;
                    wynik[i] %= 10;

                }

            }

        }

        wynik[i] += 48;
        //printf("surplus: %d wynik: %c\n", surplus, wynik[i]);

    }

    if(wynik[len1 + len2] == 48 && wynik[len1 + len2 - 1] == 48)
        wynik[len1 + len2 - 1] = '\0';
    else if(wynik[len1 + len2] == 48 && wynik[len1 + len2 - 1] != 48)
        wynik[len1 + len2] = '\0';


    /*for(int i = len1 + len2 - 2; i >= 0; i--)
        printf("%c", wynik[i]);

    printf("\n");*/

    return wynik;

}

char* mnozenieStringow(char *string1, int len1, char *string2, int len2){

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

    char* wynik = malloc(sizeof(char) * (len1 + len2 + 2));

    for(int i = 0; i < len1+ len2 + 2; i++)
        wynik[i] = 0;

    surplus = 0;
    int offset = 0;

    for(int i = 0; i < len1 + len2 + 1; i++){

        wynik[i] = surplus;
        surplus = 0;

        offset = 0;

        for(int j = 0; j < len2; j++){

            if((i-offset >= 0 && i-offset <= len1 + 1) && wyniki[j][i-offset] != 0){
                //printf("do %d dodaje %d j: %d\n", wynik[i], wyniki[j][i-offset] - 48, i-offset);
                wynik[i] += (wyniki[j][i-offset] - 48);

                if(wynik[i] > 9){

                    surplus += wynik[i] / 10;
                    wynik[i] %= 10;

                }

            }

            offset++;
        }

        wynik[i] += 48;
        //printf("surplus: %d wynik: %c\n", surplus, wynik[i]);

    }

    if(wynik[len1 + len2] == 48 && wynik[len1 + len2 - 1] == 48)
        wynik[len1 + len2 - 1] = '\0';
    else if(wynik[len1 + len2] == 48 && wynik[len1 + len2 - 1] != 48)
        wynik[len1 + len2] = '\0';


    /*for(int i = len1 + len2 - 2; i >= 0; i--)
        printf("%c", wynik[i]);

    printf("\n");*/

    return wynik;

}

void karatsuba(char *string1, int len1, char *string2, int len2){

    unsigned short srodek = (len1 % 2 == 0)? len1 / 2: len1 / 2 + 1;

    printf("srodek %d\n", srodek);

    //printf("%c %c\n", string1[len1 - srodek], string2[len2 - srodek]);
    for(int i = 0; i < len1 - srodek; i++)
        printf("%c", string1[i]);

    printf(" ");

    for(int i = len1 - srodek; i < len1; i++)
        printf("%c", string1[i]);

    printf("\n");

    for(int i = 0; i < len2 - srodek; i++)
        printf("%c", string2[i]);

    printf(" ");

    for(int i = len2 - srodek; i < len2; i++)
        printf("%c", string2[i]);

    //printf("\n%d %d\n", len1 - srodek, len2 - srodek);

    char* aStep = mnozenieStringow(string1, len1 - srodek, string2, len2 - srodek);
    char* bStep = mnozenieStringow(string1 + len1 - srodek, srodek, string2 + len2 - srodek, srodek);

    printf("\n%s\n%s\n", aStep, bStep);

    char* cStep = mnozenieStringow()

    free(aStep);
    free(bStep);
}

int main(){

    int n;
    scanf("%d ", &n);

    char liczba;
    char *input1 = NULL;
    char *input2 = NULL;
    int size1 = 10001;
    int size2 = 10001;

    input1 = malloc(sizeof(char) * size1);
    input2 = malloc(sizeof(char) * size2);

    for(int i = 0; i < n; i++){

        int i = 0;

        while(liczba != ' '){

            liczba = getc(stdin);

            //printf("liczba: %c\n", liczba);

            input1[i] = liczba;

            i++;

            //printf("string: %s\n", input1);

        }

        i--;

        input1[i] = '\0';

        //printf("%s [%d]", input1, i);

        int j = 0;

        while(liczba != '\n'){

            liczba = getc(stdin);

            //printf("liczba: %c\n", liczba);

            input2[j] = liczba;

            j++;

            //printf("string: %s\n", input1);

        }

        j--;

        input2[j] = '\0';

        //printf("%s [%d]\n", input2, j);

        if(input1[0] - 48 == 0 || input2[0] - 48 == 0)
            printf("0\n");
        else if(input1[0] - 48 == 1 && i == 1)
            printf("%s\n", input2);
        else if(input2[0] - 48 == 1 && j ==1)
            printf("%s\n", input1);
        else if(i >= j)
            karatsuba(input1, i, input2, j);
        else
            karatsuba(input2, j, input1, i);

    }

	free(input1);
    free(input2);

    return 0;

}
