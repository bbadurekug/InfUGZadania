//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"tommath/tommath.h"

/*char* add(char* num1, char* num2){

    char* number = NULL;
    char* longerNum = NULL;
    char* shorterNum = NULL;
    int num1Len = strlen(num1);
    int num2Len = strlen(num2);

    int carry = 0;
    int numberLen = 0;
    int shorterLen = 0;

    if(num1Len > num2Len){

        numberLen = num1Len;
        shorterLen = num2Len;
        longerNum = malloc((numberLen + 1) * sizeof(char));
        shorterNum = malloc((shorterLen + 1) * sizeof(char));
        strcpy(longerNum, num1);
        strcpy(shorterNum, num2);

    }
    else{

        numberLen = num2Len;
        shorterLen = num1Len;
        longerNum = malloc((numberLen + 1) * sizeof(char));
        shorterNum = malloc((shorterLen + 1) * sizeof(char));
        strcpy(longerNum, num2);
        strcpy(shorterNum, num1);

    }

    number = malloc((numberLen + 1) * sizeof(char));

    number[numberLen] = '\0';

    for(int i = 1; i <= shorterLen; i++){

        number[numberLen - i] = (longerNum[numberLen - i] - '0') + (shorterNum[shorterLen - i] - '0') + carry;

        if(number[numberLen - i] > 9){

            carry = number[numberLen - i] / 10;
            number[numberLen - i] %= 10;

        }
        else{

            carry = 0;

        }

        number[numberLen - i] += '0';

    }

    for(int i = shorterLen + 1; i <= numberLen; i++){

        number[numberLen - i] = (longerNum[numberLen - i] - '0') + carry;

        if(number[numberLen - i] > 9){

            carry = number[numberLen - i] / 10;
            number[numberLen - i] %= 10;

        }
        else{

            carry = 0;

        }

        number[numberLen - i] += '0';

    }

    free(longerNum);
    free(shorterNum);

    return number;

}*/

char* getLongNumber(FILE* sourceFile){

    char* number = NULL;
    int numberLen = 0;
    number = malloc((numberLen + 1) * sizeof(char));

    char input = getc(sourceFile);

    while(input >= '0' && input <= '9'){

        number = realloc(number, (++numberLen + 1) * sizeof(char));

        number[numberLen - 1] = input;
        number[numberLen] = '\0';

        input = getc(sourceFile);

    }

    //printf("%s\n", number);

    return number;

}

void keys(){

    FILE* elgamal = NULL;
    elgamal = fopen("./elgamal.txt", "r");

    char* num1 = NULL;
    char* num2 = NULL;

    num1 = getLongNumber(elgamal);
    num2 = getLongNumber(elgamal);

    fclose(elgamal);

    mp_int p, g, random, result;

    mp_init(&p);
    mp_init(&g);
    mp_init(&random);
    mp_init(&result);

    mp_read_radix(&p, num1, 10);
    mp_read_radix(&g, num2, 10);

    srand(time(NULL));
    mp_rand(&random, 128);

    mp_int mod;
    mp_init(&mod);

    mp_read_radix(&mod, "10", 10);
    mp_expt_n(&mod, 90, &mod);

    mp_mod(&random, &mod, &random);

    char private_key[256];
    mp_to_radix(&random, private_key, 256, NULL, 10);

    //MOZE TO POPRAWIC????
    mp_exptmod(&g, &random, &p, &result);

    char public_key[256];
    mp_to_radix(&result, public_key, 256, NULL, 10);

    //printf("Private:\n%s\nPublic:\n%s\n", private_key, public_key);

    FILE* private_file = NULL;
    private_file = fopen("./private.txt", "w");

    fprintf(private_file, "%s\n%s\n%s\n", num1, num2, private_key);
    fclose(private_file);

    FILE* public_file = NULL;
    public_file = fopen("./public.txt", "w");

    fprintf(public_file, "%s\n%s\n%s\n", num1, num2, public_key);
    fclose(public_file);

    free(num1);
    free(num2);

    mp_clear_multi(&p, &g, &random, &result, NULL);

}

void encrypt(){

    FILE* public_file = NULL;
    public_file = fopen("./public.txt", "r");

    char* p_text = NULL;
    char* g_text = NULL;
    char* public_key = NULL;

    p_text = getLongNumber(public_file);
    g_text = getLongNumber(public_file);
    public_key = getLongNumber(public_file);

    fclose(public_file);

    //printf("%s\n", public_key);

    mp_int key_public, p, g, m, k;
    mp_init(&key_public);
    mp_init(&p);
    mp_init(&g);
    mp_init(&m);
    mp_init(&k);

    mp_read_radix(&p, p_text, 10);
    mp_read_radix(&g, g_text, 10);
    mp_read_radix(&key_public, public_key, 10);

    free(public_key);
    free(p_text);
    free(g_text);

    FILE* plain = NULL;
    plain = fopen("./plain.txt", "r");

    char* plain_text = NULL;
    plain_text = getLongNumber(plain);
    fclose(plain);
    mp_read_radix(&m, plain_text, 10);

    int compare_result = 0;

    compare_result = mp_cmp(&m, &key_public);

    if(compare_result != MP_LT){

        printf("Blad! m nie jest mniejsze od p!");
        return;

    }

    mp_int tmp, euklides_result;
    mp_init(&tmp);
    mp_init(&euklides_result);

    mp_sub_d(&p, 2, &tmp);
    mp_exch(&tmp, &p);

    srand(time(NULL));

    do{

        mp_rand(&k, mp_count_bits(&p));
        mp_mod(&k, &p, &tmp);
        mp_exch(&tmp, &k);
        mp_add_d(&k, 2, &tmp);
        mp_exch(&tmp, &k);

        //MOZE TO POPRAWIC
        mp_gcd(&k, &p, &euklides_result);

        compare_result = mp_cmp_d(&euklides_result, 1);

    }while(compare_result != MP_EQ);

    mp_clear(&euklides_result);

    mp_int c1, c2;
    mp_init(&c1);
    mp_init(&c2);

    mp_add_d(&p, 2, &tmp);
    mp_exch(&tmp, &p);

    //MOZE POPRWAIC
    mp_exptmod(&g, &k, &p, &c1);

    mp_exptmod(&key_public, &k, &p, &tmp);
    mp_mulmod(&tmp, &m, &p, &c2);

    char c1_text[256];
    mp_to_radix(&c1, c1_text, 256, NULL, 10);

    char c2_text[256];
    mp_to_radix(&c2, c2_text, 256, NULL, 10);

    //printf("%s\n%s\n", c1_text, c2_text);

    FILE* crypto = NULL;
    crypto = fopen("./crypto.txt", "w");

    fprintf(crypto, "%s\n%s\n", c1_text, c2_text);

    fclose(crypto);

    mp_clear_multi(&c1, &c2, NULL);

    mp_clear_multi(&key_public, &p, &g, &m, &k, &tmp, NULL);

}

void decrypt(){

    FILE* private_file = NULL;
    private_file = fopen("./private.txt", "r");

    char* p_text = NULL;
    char* g_text = NULL;
    char* private_key = NULL;

    p_text = getLongNumber(private_file);
    g_text = getLongNumber(private_file);
    private_key = getLongNumber(private_file);

    fclose(private_file);

    //printf("%s\n", private_key);

    mp_int key_private, p, g, m;
    mp_init(&key_private);
    mp_init(&p);
    mp_init(&g);
    mp_init(&m);

    mp_read_radix(&p, p_text, 10);
    mp_read_radix(&g, g_text, 10);
    mp_read_radix(&key_private, private_key, 10);

    free(private_key);
    free(p_text);
    free(g_text);

    FILE* crypto = NULL;
    crypto = fopen("./crypto.txt", "r");

    char* c1_text = NULL;
    char* c2_text = NULL;
    c1_text = getLongNumber(crypto);
    c2_text = getLongNumber(crypto);
    fclose(crypto);

    mp_int c1, c2, s, tmp;
    mp_init(&c1);
    mp_init(&c2);
    mp_init(&s);
    mp_init(&tmp);

    mp_read_radix(&c1, c1_text, 10);
    mp_read_radix(&c2, c2_text, 10);

    mp_exptmod(&c1, &key_private, &p, &s);

    //POPRWAIC?
    mp_invmod(&s, &p, &tmp);
    mp_exch(&tmp, &s);

    mp_mulmod(&c2, &s, &p, &m);

    char m_text[256];
    mp_to_radix(&m, m_text, 256, NULL, 10);

    //printf("%s\n", m_text);

    FILE* decrypt = NULL;
    decrypt = fopen("./decrypt.txt", "w");

    fprintf(decrypt, "%s\n", m_text);

    fclose(decrypt);

    mp_clear_multi(&key_private, &p, &g, &c1, &c2, &s, &m, &tmp, NULL);

}

int main(int argc, char *argv[]){

    if(argc != 2){

        fprintf(stderr, "Nie podano zadnej opcji. Podaj jedna opcje.");
        return 1;

    }

    char type;

    switch(argv[1][1]){

        case 'k':

            printf("Generowanie kluczy\n");
            keys();

            break;

        case 'e':

            printf("Szyfrowanie\n");
            encrypt();

            break;

        case 'd':

            printf("Odszyfrowanie\n");
            decrypt();

            break;

        case 's':

            printf("Generowanie podpisu\n");

            break;

        case 'v':

            printf("Weryfikacja\n");

            break;

       default:

            printf("Nie podano poprawnej pierszej opcji.");
            return 1;

            break;

    }

    return 0;

}
