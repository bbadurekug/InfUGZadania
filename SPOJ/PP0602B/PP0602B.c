#include<stdio.h>

void obrocRamke(int l, int k, int arr[l][k]){

    int temp = arr[0][0];

    for(int i = 0; i < (k-1); i++)
        arr[0][i] = arr[0][i+1];

    for(int i = 0; i < (l-1); i++)
        arr[i][k-1] = arr[i+1][k-1];

    for(int i = (k-1); i >= 0; i--)
        arr[l-1][i] = arr[l-1][i-1];

    for(int i = (l-1); i >= 1; i--)
        arr[i][0] = arr[i-1][0];

    arr[1][0] = temp;

}

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        int l,k;

        scanf("%d %d", &l, &k);

        int arr[l][k];

        for(int j = 0; j < l; j++){

            for(int o = 0; o < k; o++){

                scanf("%d", &arr[j][o]);

            }

        }

        obrocRamke(l, k, arr);

         for(int j = 0; j < l; j++){

            for(int o = 0; o < k; o++){

                printf("%d ", arr[j][o]);

            }

            printf("\n");

        }

    }

    return 0;

}
