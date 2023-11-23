#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int powerOf10(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

double convertFrontInBase2(double n){

    n = fabs(n);

    //printf("%f\n", n);

    int front = (int)n;

    n = 0;

    int division = front, rest;

    int iteration = 0;

    while(division != 0){

        rest = division % 2;
        //printf("rest %d\n", rest);
        if(rest)
            n = n + powerOf10(10, iteration) * rest;
        division /= 2;
        //printf("div %d\n", division);
        iteration++;
        //printf("%d %f\n",iteration, n);
    }

    return n;

}

double convertBackInBase2(double n){

    n = fabs(n);

    int front = (int)n;
    float back = n - front;

    n = 0;

    float multi = back;
    float rest;

    int iteration = 1;

    while(multi != 0){

        multi *= 2.0;
        //printf("multi: %f\n", multi);
        rest = (int)multi;
        if(multi >= 1)
            multi -= 1;
        //printf("rest: %f\n", rest);
        n += rest / powerOf10(10, iteration);
        iteration++;
    }

    return n;

}

int iterationsFront(double n){

    int front = (int)n;

    n = 0;

    int division = front, rest;

    int iteration = 0;

    while(division != 0){

        rest = division % 2;
        if(rest)
            n = n + powerOf10(10, iteration) * rest;
        division /= 2;
        iteration++;
    }

    return iteration - 1;
}

int iterationsBack(double n){

    int front = (int)n;
    float back = n - front;

    n = 0;

    float multi = back;
    float rest;

    int iteration = 1;

    while(multi != 0){

        multi *= 2.0;
        //printf("multi: %f\n", multi);
        rest = (int)multi;
        if(multi >= 1)
            multi -= 1;
        //printf("rest: %f\n", rest);
        n += rest / powerOf10(10, iteration);
        iteration++;
    }

    return iteration - 1;

}

void printfloat(double n){

    double signDouble = (n >= 0)? 0: 1;

    n = fabs(n);

    double mantisaDouble = (convertFrontInBase2(n) + convertBackInBase2(n)) * (int)pow(10,iterationsBack(n));

    //printf("%f\n", mantisaDouble);

    float exponentValue = (float)iterationsFront(n) + 127.0;

    double exponentDouble = convertFrontInBase2(exponentValue);

    //printf("%f\n", exponentValue);
    //printf("%f\n", exponentDouble);

    //printf("%f\n", signDouble);

    int mantisa = (int)mantisaDouble, exponent = (n != 0)?(int)exponentDouble : 0, sign = (int)signDouble;

    //printf("%d\n", mantisa);
    //printf("%d\n", exponent);
    //printf("%d\n", sign);

    int mantisaLength = (mantisa != 0)? log10(mantisa) : 0;

    //printf("%d\n", mantisaLength);

    char liczba[33] = {0};

    sprintf(liczba,"%d", sign);

    //printf("liczba %s\n", liczba);

    int exponentLength = (exponent != 0)? log10(exponent) + 1 : 0;

    for(int i = exponentLength; i < 8; i++){
        sprintf(liczba,"%s%d", liczba, 0);
    }

    //printf("liczba %s\n", liczba);

    sprintf(liczba,"%s%d", liczba, exponent);

    if((mantisaLength != 0) && ((mantisa / (int)pow(10, mantisaLength-1)) % 10 == 0))
        sprintf(liczba,"%s%d", liczba, 0);
    if(mantisa)
        mantisa -= (int)pow(10, mantisaLength);
    sprintf(liczba,"%s%d", liczba, mantisa);



    //printf("liczba %s\n", liczba);

    for(int i = mantisaLength; i < 23; i++){
        sprintf(liczba,"%s%d", liczba, 0);
    }

    printf("liczba %s\n", liczba);

    int bit = 0;
    int base16 = 0;

    for(int i = 0; i < 8; i++){

        for(int j = 0; j < 4; j++){

            base16 += (int)pow(2,3-j) * (liczba[j+(bit*4)] - '0');

        }
        if(base16 > 9)
            printf("%c", base16 + 87);
        else

        if(bit % 2 == 0){
            if(base16 != 0)
                printf("%d", base16);
        }
        else
            printf("%d", base16);
        base16 = 0;
        bit++;
        if(bit % 2 == 0)
            printf(" ");

    }


}

int main(){

    int t;
    double n;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        scanf("%lf", &n);
        printfloat(n);

    }

    return 0;

}
