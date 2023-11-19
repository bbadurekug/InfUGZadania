#include <stdio.h>

int main(){

    int N, koniec = 0;

    int a, b;

    scanf("%d", &N);

    for(int i = 0; i < N; i++){

        scanf("%d %d", &a, &b);

        int reszta = 1, wieksza, mniejsza, dzielnik;

        if(a > b)
        {
            wieksza = a;
            mniejsza = b;
        }
        else{
            wieksza = b;
            mniejsza = a;
        }

        while(reszta != 0){

            reszta = wieksza % mniejsza;
            dzielnik = reszta;
            wieksza = mniejsza;
            mniejsza = reszta;
        }

        printf("%d\n", wieksza);

    }


    return 0;

}
