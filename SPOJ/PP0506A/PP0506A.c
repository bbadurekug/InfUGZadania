#include<stdio.h>
#include<math.h>
#include<string.h>

float obliczanieOdleglosci(int x, int y){

    float odleglosc = sqrt((x*x) + (y*y));

    return odleglosc;

}

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        int n;

        scanf("%d", &n);

        char nazwy[n][11];
        float odleglosci[n];
        int x[n],y[n];

        for(int j = 0; j < n; j++){



            scanf(" %s", &nazwy[j]);
            scanf("%d", &x[j]);
            scanf("%d", &y[j]);
            odleglosci[j] = obliczanieOdleglosci(x[j],y[j]);
            //printf("%c ", nazwy[j]);
            //printf("%d ", x[j]);
            //printf("%d ", y[j]);
            //printf("%f\n", odleglosci[j]);


        }

        char tempChar[11];
        float tempOdleg;
        int tempX, tempY;

        sort:

        for(int k = 0; k < (n-1); k++){

            if(odleglosci[k] > odleglosci[k+1]){

                tempOdleg = odleglosci[k];
                odleglosci[k] = odleglosci[k+1];
                odleglosci[k+1] = tempOdleg;
                //tempOdleg = 0;

                strcpy(tempChar, nazwy[k]);
                strcpy(nazwy[k], nazwy[k+1]);
                strcpy(nazwy[k+1], tempChar);

                tempX = x[k];
                x[k] = x[k+1];
                x[k+1] = tempX;
                //tempX = 0;

                tempY = y[k];
                y[k] = y[k+1];
                y[k+1] = tempY;
                //tempY = 0;

                goto sort;

            }
        }

        for(int l = 0; l < n; l++){

            printf("%s %d %d\n", nazwy[l], x[l], y[l]);

        }



    }

    return 0;

}
