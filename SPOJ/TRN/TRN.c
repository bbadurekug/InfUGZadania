#include<stdio.h>

int main(){

    int m, n;

    scanf("%d %d", &m, &n);

    int macierz[m][n];

    for(int j = 0; j < m; j++){
        for(int i = 0; i < n; i++){

            scanf("%d", &macierz[j][i]);
            //printf("%d ", macierz[0][i]);
        }

        //printf("\n");
    }

    for(int j = 0; j < n; j++){
        for(int i = 0; i < m; i++){

            //scanf("%d", &macierz[0][i]);
            printf("%d ",macierz[i][j]);
        }

        printf("\n");
    }

    return 0;

}
