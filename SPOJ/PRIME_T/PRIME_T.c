#include<stdio.h>

int main(){

    int n;

    scanf("%d", &n);

    int czyPierwsza;

    char nieJest = 0;

    for(int i = 0; i < n; i++){

        scanf("%d", &czyPierwsza);

        if(czyPierwsza == 1){

            nieJest = 1;

        }
        else{

            for(int j = 2; j < czyPierwsza; j++){


                if(czyPierwsza % j == 0){

                    nieJest = 1;

                }

            }
        }
        if(nieJest == 1){

            printf("NIE\n");
            nieJest = 0;

        }
        else
            printf("TAK\n");
    }

    return 0;

}
