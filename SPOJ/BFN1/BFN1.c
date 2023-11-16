#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(){

    int t,n;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        scanf("%d", &n);

        int dlugoscN;

        int palindrom = 0;

        char czyPalindrom = 0, proby = 0;

        jeszczeRaz:

        dlugoscN = (int)log10(n) + 1;

        for(int j = 0; j < (dlugoscN/2); j++){

            //printf("%d ", (n / (int)pow(10, dlugoscN-1-j))%10);
            //printf("%d\n", (n % (int)pow(10, j+1)) / (int)pow(10, j));

            if(((n / (int)pow(10, dlugoscN-1-j))%10) == ((n % (int)pow(10, j+1)) / (int)pow(10, j))){

                czyPalindrom += 1;

            }

        }

        if(czyPalindrom == (dlugoscN/2)){

            printf("%d %d\n", n, proby);
            czyPalindrom = 0;
            proby = 0;

        }
        else{

            czyPalindrom = 0;

            for(int k = 0; k < dlugoscN; k++){

                palindrom = palindrom * 10 + ((n % (int)pow(10, k+1)) / (int)pow(10, k));
                //printf("%d\n", palindrom);

            }

            n += palindrom;

            palindrom = 0;

            //printf("%d\n", n);
            proby++;
            goto jeszczeRaz;
        }


    }

    return 0;

}
