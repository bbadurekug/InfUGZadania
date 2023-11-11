#include<stdio.h>

int main(){

    int n;

    printf("Podaj liczbe: \n");
    scanf("%d", &n);

    for(int i = 2; i <= 6; i++){

        if(n%i == 0){

            printf("%d jest podzielne przez %d ", n, i);
            return 0;
        }

    }

    printf("%d nie jest podzielne przez zadna liczbe z zakresu 2-6.", n);

    return 0;

}
