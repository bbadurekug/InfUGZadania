#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>

void convertToBase(int base, int number){

    int size = 2;
    int* converted = malloc(sizeof(int) * size);
    int i = 0;

    while(number != 0){

        if(i == size){

            size *= 2;
            converted = realloc(converted, sizeof(int) * size);
            //printf("realloc activated\n");

        }

        converted[i] = number % base;
        number /= base;
        i++;

    }

    char makeItBig[2];

    for(int j = i-1; j >= 0; j--){

        sprintf(makeItBig, "%x", converted[j]);
        makeItBig[0] = toupper(makeItBig[0]);
        printf("%s", makeItBig);

    }

    free(converted);

    printf(" ");

}

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        int n;

        scanf("%d", &n);

        convertToBase(16,n);
        convertToBase(11,n);

        printf("\n");

    }

    return 0;

}
