//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<gmp.h>

#define     CHECKS  100

int getLongNumber(FILE* sourceFile, char** numberResult){

    char* number = NULL;
    int numberLen = 0;
    number = malloc((numberLen + 1) * sizeof(char));

    number[numberLen] = '\0';

    char input = getc(sourceFile);

    while(input >= '0' && input <= '9'){

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

size_t rabinmillerPow(mpz_t** bArray, const mpz_t a, const mpz_t n, const mpz_t r){

    size_t k = 0;
    mpz_t m, nMinusOne;
    mpz_t* array = NULL;

    mpz_inits(m, nMinusOne, NULL);

    if(mpz_cmp_ui(r, 0) == 0){

        mpz_sub_ui(nMinusOne, n, 1);

        //gmp_printf("n-1: %Zd ", nMinusOne);

        mpz_set(m, nMinusOne);

        while(mpz_even_p(m)){

            mpz_fdiv_q_2exp(m, m, 1);
            k++;

        }

    }
    else{

        //gmp_printf("r: %Zd ", r);

        mpz_set(m, r);

        while(mpz_even_p(m)){

            mpz_fdiv_q_2exp(m, m, 1);
            k++;

        }

    }

    //gmp_printf("m: %Zd k: %d a: %Zd\n", m, k, a);

    array = malloc(sizeof(mpz_t));
    mpz_init(array[0]);

    mpz_powm(array[0], a, m, n);

    //gmp_printf("0: %Zd %d\n", array[0], k);

    for(int i = 0; i < k; i++){

        array = realloc(array, sizeof(mpz_t) * (i + 2));
        mpz_init(array[i+1]);

        mpz_mul(array[i+1], array[i], array[i]);
        mpz_mod(array[i+1], array[i+1], n);

        //gmp_printf("%d: %Zd %d\n", i+1, array[i+1], k);

    }

    mpz_clears(m, nMinusOne, NULL);
    *bArray = array;

    return k;

}

void rabinmiller(){

    FILE* wejscie = NULL;
    wejscie = fopen("./wejscie.txt", "r");

    int nInupts = 0;
    char* nText = NULL;
    char* r1Text = NULL;
    char* r2Text = NULL;

    if(getLongNumber(wejscie, &nText) == 0){

        fprintf(stderr, "No input!");

    }
    else{

        nInupts++;

    }

    if(getLongNumber(wejscie, &r1Text) == 1){

        nInupts++;

    }

    if(getLongNumber(wejscie, &r2Text) == 1){

        nInupts++;

    }

    fclose(wejscie);

    mpz_t n, a, r1, r2, r, nMinusOne, nMinusTwo, nwdResult;
    mpz_t* bArray;
    size_t k;
    gmp_randstate_t randState;

    mpz_inits(n, a, r1, r2, r, nMinusOne, nMinusTwo, nwdResult, NULL);
    gmp_randinit_default(randState);
    gmp_randseed_ui(randState, time(NULL));

    mpz_set_str(n, nText, 10);

    if(r1Text != NULL && r2Text == NULL){

        mpz_set_str(r, r1Text, 10);

    }
    else if(r1Text != NULL && r2Text != NULL){

        mpz_set_str(r1, r1Text, 10);
        mpz_set_str(r2, r2Text, 10);
        mpz_mul(r, r1, r2);
        mpz_sub_ui(r, r, 1);

    }
    else{

        mpz_set_str(r, "0", 10);

    }

    mpz_clears(r1, r2, NULL);

    mpz_set_str(a, "1", 10);

    //printf("%s, %s, %s\n", nText, r1Text, r2Text);

    free(nText);
    if(r1Text != NULL) free(r1Text);
    if(r2Text != NULL) free(r2Text);

    //gmp_printf("%Zd, %Zd\n", n, r);

    mpz_sub_ui(nMinusOne, n, 1);
    mpz_sub_ui(nMinusTwo, n, 2);

    int isPrime = 1;

    for(int i = 0; i < CHECKS; i++){

        mpz_urandomm(a, randState, nMinusTwo);
        mpz_mod(a, a, nMinusTwo);
        mpz_add_ui(a, a, 2);

        //gmp_printf("a: %Zd\n", a);

        mpz_gcd(nwdResult, a, n);

        if(mpz_cmp_ui(nwdResult, 1) == 0){

            k = rabinmillerPow(&bArray, a, n, r);

            //gmp_printf("enterd1 %Zd\n", bArray[k]);

            if(mpz_cmp_ui(bArray[k], 1) == 0){

                //gmp_printf("Potencjalnie zlozona\n");

                for(int j = 0; j < k; j++){

                    if(mpz_cmp_ui(bArray[j+1], 1) == 0 && mpz_cmp_si(bArray[j], -1) != 0){

                        mpz_sub_ui(bArray[j], bArray[j], 1);
                        mpz_gcd(nwdResult, bArray[j], n);
                        //gmp_printf("DZIELNIK %Zd\n", nwdResult);
                        if(mpz_cmp_ui(nwdResult, 1) != 0 && mpz_cmp(nwdResult, n) != 0){
                            isPrime = -1;
                            goto exitLoop;
                        }

                    }

                }

            }

        }
        else{

            //gmp_printf("DZIELNIK %Zd\n", nwdResult);
            isPrime = 0;
            //goto clearMem;

        }

    }

    exitLoop:

    FILE* wyjscie = NULL;
    wyjscie = fopen("./wyjscie.txt", "w");

    if(isPrime == 1) fprintf(wyjscie, "prawdopodobnie pierwsza\n");
    if(isPrime == 0) fprintf(wyjscie, "na pewno złożona\n");
    if(isPrime == -1) gmp_fprintf(wyjscie, "%Zd\n", nwdResult);

    fclose(wyjscie);

    //clearMem:

    gmp_randclear(randState);
    for(int i = 0; i < k; i++){
        mpz_clear(bArray[i]);
    }
    free(bArray);
    mpz_clears(n, a, r, nMinusOne, nMinusTwo, nwdResult, NULL);

}

void fermat(){

    FILE* wejscie = NULL;
    wejscie = fopen("./wejscie.txt", "r");

    char* nText;

    if(getLongNumber(wejscie, &nText) == 0){

        fprintf(stderr, "No input!");
        return;

    }

    fclose(wejscie);

    mpz_t n, nMinusOne, nMinusTwo, a, nwdResult, powResult;
    gmp_randstate_t randState;

    mpz_inits(n, nMinusOne, nMinusTwo, a, nwdResult, powResult, NULL);
    gmp_randinit_default(randState);
    gmp_randseed_ui(randState, time(NULL));

    mpz_set_str(n, nText, 10);
    mpz_set_str(a, "1", 10);

    free(nText);

    mpz_sub_ui(nMinusOne, n, 1);
    mpz_sub_ui(nMinusTwo, n, 2);

    int isPrime = 1;

    for(int i = 0; i < CHECKS; i++){

        mpz_urandomm(a, randState, nMinusTwo);
        mpz_add_ui(a, a, 2);

        //gmp_printf("%Zd\n", a);

        mpz_gcd(nwdResult, a, n);

        if(mpz_cmp_ui(nwdResult, 1) == 0){

            mpz_powm(powResult, a, nMinusOne, n);

            if(mpz_cmp_ui(powResult, 1) != 0){

                isPrime = 0;
                goto exitLoop;

            }

        }

    }

    exitLoop:

    FILE* wyjscie = NULL;
    wyjscie = fopen("./wyjscie.txt", "w");

    if(isPrime == 1) fprintf(wyjscie, "prawdopodobnie pierwsza\n");
    if(isPrime == 0) fprintf(wyjscie, "na pewno złożona\n");

    fclose(wyjscie);

    //clearMem:

    gmp_randclear(randState);
    mpz_clears(n, nMinusOne, nMinusTwo, a, nwdResult, powResult, NULL);

}

int main(int argc, char *argv[]){

    if(argc > 2){

        fprintf(stderr, "Podano zbyt wiele opcji!");
        return 1;

    }
    else if(argc == 1){

        printf("Algorytm Rabina-Millera\n");
        rabinmiller();

    }
    else{

        switch(argv[1][1]){

            case 'f':

                printf("Test Fermata\n");
                fermat();

                break;

           default:

                printf("Nie podano poprawnej opcji.");
                return 1;

                break;

        }

    }

	return 0;
}
