#include<stdio.h>
#include<math.h>

void wiatraczek(int n){

    char wiatrak[2*n][2*n];

    int gwiazdkiLewoGora = (n >= 0)? 1: abs(n);
    int kropkiLewoGora = (n >= 0)? n - 1: 0;

    int gwiazdkiPrawoGora = (n >= 0)? n: 1;
    int kropkiPrawoGora = (n >= 0)? 0: abs(n) - 1;

    int gwiazdkiLewoDol = (n >= 0)? 1: abs(n);
    int kropkiLewoDol = (n >= 0)? n - 1: 0;

    int gwiazdkiPrawoDol = (n >= 0)? n: 1;
    int kropkiPrawoDol = (n >= 0)? 0: abs(n) - 1;

    if(n >= 0){

        for(int p = 0; p < n; p++){
            for(int g = gwiazdkiLewoGora; g > 0; g--){

                printf("*");

            }
            gwiazdkiLewoGora++;
            for(int k = kropkiLewoGora; k > 0; k--){

                printf(".");

            }
            kropkiLewoGora--;

            for(int g = gwiazdkiPrawoGora; g > 0; g--){

                printf("*");

            }
            gwiazdkiPrawoGora--;
            for(int k = kropkiPrawoGora; k > 0; k--){

                printf(".");

            }
            kropkiPrawoGora++;
            printf("\n");
        }

        for(int p = 0; p < n; p++){

            for(int k = kropkiLewoDol; k > 0; k--){

                printf(".");

            }
            kropkiLewoDol--;

            for(int g = gwiazdkiLewoDol; g > 0; g--){

                printf("*");

            }
            gwiazdkiLewoDol++;

            for(int k = kropkiPrawoDol; k > 0; k--){

                printf(".");

            }
            kropkiPrawoDol++;

            for(int g = gwiazdkiPrawoDol; g > 0; g--){

                printf("*");

            }
            gwiazdkiPrawoDol--;

            printf("\n");
        }
    }
    else{

        for(int p = 0; p < abs(n); p++){

            for(int k = kropkiLewoGora; k > 0; k--){

                printf(".");

            }
            kropkiLewoGora++;

            for(int g = gwiazdkiLewoGora; g > 0; g--){

                printf("*");

            }
            gwiazdkiLewoGora--;

            for(int k = kropkiPrawoGora; k > 0; k--){

                printf(".");

            }
            kropkiPrawoGora--;

            for(int g = gwiazdkiPrawoGora; g > 0; g--){

                printf("*");

            }
            gwiazdkiPrawoGora++;

            printf("\n");
        }

        for(int p = 0; p < abs(n); p++){

            for(int g = gwiazdkiLewoDol; g > 0; g--){

                printf("*");

            }
            gwiazdkiLewoDol--;

            for(int k = kropkiLewoDol; k > 0; k--){

                printf(".");

            }
            kropkiLewoDol++;


            for(int g = gwiazdkiPrawoDol; g > 0; g--){

                printf("*");

            }
            gwiazdkiPrawoDol++;

            for(int k = kropkiPrawoDol; k > 0; k--){

                printf(".");

            }
            kropkiPrawoDol--;


            printf("\n");
        }

    }

    printf("\n");

}

int main(){

    int t = 100;

    int n;

    while(n){

        scanf("%d", &n);

        wiatraczek(n);

    }

    return 0;

}
