#include<stdio.h>

int main(){

    int n;
    scanf("%d ", &n);

    char buffer[12];
    int pesel[11];
    int i;
    int wynik;

    for(int k = 0; k < n; k++){

        i = 0;

        gets(buffer);

        while(buffer[i] != '\0' && buffer[i] != '\n'){
            pesel[i] = buffer[i] - 48;
            i++;
        }

        wynik = pesel[0] + pesel[1] * 3 + pesel[2] * 7 + pesel[3] * 9 + pesel[4] + pesel[5] * 3 + pesel[6] * 7 + pesel[7] * 9 + pesel[8] + pesel[9] * 3 + pesel[10];

        if(wynik % 10 == 0 && wynik > 0)
            printf("D\n");
        else
            printf("N\n");

    }


    return 0;

}
