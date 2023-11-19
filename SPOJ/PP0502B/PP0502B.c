#include<stdio.h>

int main(){

    int t,n;

    int arr[100];

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        scanf("%d", &n);

        for(int j = 0; j < n; j++){

            scanf("%d", &arr[(n-1) - j]);
        }
        for(int j = 0; j < n; j++){

            printf("%d ", arr[j]);
        }

        printf("\n");

    }

    return 0;

}
