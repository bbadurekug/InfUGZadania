#include<stdio.h>

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        int n;

        scanf("%d", &n);

        int arr[n];

        for(int j = 0; j < n; j++){

            scanf("%d", &arr[j]);

        }

        for(int p = 1; p < n; p+=2){

            printf("%d ", arr[p]);

        }

        for(int np = 0; np < n; np+=2){

            printf("%d ", arr[np]);

        }

        printf("\n");

    }

    return 0;

}
