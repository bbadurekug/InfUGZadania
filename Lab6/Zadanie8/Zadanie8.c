#include<stdio.h>

int znajdzOstatniZnak(char slowo[]){

    static int i = 0;

    if(slowo[i] != '\0'){
        i++;
        znajdzOstatniZnak(slowo);
        }
    else
        return i-1;

}

int czyPalindrom(char slowo[]){


    static int pierwszy = 0;
    static int proba = 0;

    if(proba == znajdzOstatniZnak(slowo)/2)
        return 1;

    if(slowo[pierwszy] != slowo[(znajdzOstatniZnak(slowo) - proba)]){

        return 0;

    }
    else{

        pierwszy++;
        proba++;
        czyPalindrom(slowo);
    }

}

int main(){

    printf("Podaj slowo:\n");

    char slowo[100];

    scanf("%s", slowo);

    printf("%d",czyPalindrom(slowo));

    return 0;

}
