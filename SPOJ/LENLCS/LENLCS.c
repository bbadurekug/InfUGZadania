#include<stdio.h>

int max(int a, int b){

    if(a >= b)
        return a;
    else
        return b;

}

int nwp(int len1, char slowo1[], int len2, char slowo2[]){

    int tab[len1][len2];

    for(int i = 0; i < len1; i++){

        tab[i][0] = 0;

    }

    for(int j = 0; j < len2; j++){

        tab[0][j] = 0;

    }

    for(int i = 1; i < len1; i++){

        for(int j = 1; j < len2; j++){

            if(slowo1[i-1] == slowo2[j-1])
                tab[i][j] = tab[i-1][j-1] + 1;
            else
                tab[i][j] = max(tab[i][j-1], tab[i-1][j]);
        }

    }

    for(int i = 0; i < len1; i++){

        for(int j = 0; j < len2; j++){

            printf("%d ", tab[i][j]);
        }

        printf("\n");

    }

    return tab[len1-1][len2-1];

}

int main(){

    int D;

    scanf("%d", &D);

    for(int i = 0; i < D; i++){

        int m, n;

        scanf("%d", &n);

        n++;

        char slowo1[n];

        scanf("%s", slowo1);

        scanf("%d", &m);

        m++;

        char slowo2[m];

        scanf("%s", slowo2);

        //printf("%d %d", slowo1[n], slowo2[m]);

        printf("%d\n", nwp(n, slowo1, m, slowo2));

    }

    return 0;

}
