#include<stdio.h>

int main(){

    unsigned int D, n;

    int nSilnia;

    scanf("%d", &D);

    for(int i = 0; i < D; i++){

        scanf("%d", &n);

        if(n >= 10){

            printf("0 0\n");

        }
        else if(n == 0){

            printf("0 1\n");

        }
        else{

            nSilnia = n;

            for(int j = 1; j < n-1; j++){

                nSilnia *= (n - j);
                if((nSilnia/10) % 10 == 0 && nSilnia % 10 == 0)
                    break;

            }

            printf("%d %d\n", (nSilnia/10) % 10, nSilnia % 10);

        }

    }

    return 0;

}
