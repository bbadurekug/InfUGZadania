#include<stdio.h>
#include<string.h>

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        char slowo[2001];

        scanf("%s", slowo);

        int k = strlen(slowo) / 2;

        for(int j = 0; j < k; j++){

            printf("%c", slowo[j]);

        }

        printf("\n");

    }



}
