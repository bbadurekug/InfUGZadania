#include<stdio.h>

int main(){

    int n,i;

    while(1){

        printf("Podaj mi liczbe: \n");
        scanf("%d", &n);

        for(i = 2; i < n; i++){

            if(n%i == 0){

                printf("Twoja liczba %d nie jest pierwsza!\n", n);
                break;

            }

        }


        if(n==i){

            printf("Twoja liczba %d jest pierwsza!\n", n);

        }

    }

    return 0;

}
