#include<stdio.h>

int main(){

    int d;

    scanf("%d", &d);

    float x,y,z;

    float wynik, check;

    for(int i = 0; i < d; i++){

        scanf("%f %f %f", &x, &y, &z);

        wynik = (z * y - y - x) / (z-1);

        wynik *= 12;

        check = wynik;

        check *= 10;

        check = (int)check % 10;

        if(check < 5)
            wynik = (int)wynik;
        else
            wynik = (int)wynik + 1;

        printf("%d\n", (int)wynik);

    }

    return 0;

}
