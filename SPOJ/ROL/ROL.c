#include<stdio.h>

void shifting(int size, int arr[]){

    int temp = arr[0];

    for(int i = 0; i < size; i++){

        if(i+1 < size)
            arr[i] = arr[i+1];
        else
            arr[i] = temp;
    }

}

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

        shifting(n, arr);

        for(int j = 0; j < n; j++){

            printf("%d ", arr[j]);

        }

    }

    return 0;

}
