#include<stdio.h>

int main(){

    int t,n;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        scanf("%d", &n);

        int dod, wynik;

        for(int j = 0; j < n; j++){

            wynik = 0;

            for(int k = 0; k < n; k++){

                scanf("%d", &dod);
                wynik += dod;

            }

            printf("%d\n", wynik);
            break;

        }

    }

    return 0;

}
