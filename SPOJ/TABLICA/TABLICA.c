#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){

    int liczby[50] = {0};
    int i = 0;
    char n[50];

    fgets(n, sizeof n, stdin);

    char *nToken = strtok(n, " ");

    while(nToken != NULL){

        sscanf(nToken, "%d\n", &liczby[i]);
        //printf("%d ", liczby[i]);

        nToken = strtok(NULL, " ");

        i++;

    }

    for(int j = i-1; j >= 0; j--){

        printf("%d ", liczby[j]);

    }

    return 0;

}
