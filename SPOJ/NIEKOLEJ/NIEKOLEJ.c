#include<stdio.h>

int main(){

    int n;
    scanf("%d", &n);

    if(n == 1 || n == 2){
        printf("NIE\n");
        return 0;
    }
    else if(n == 3){
        printf("2 0 3 1\n");
        return 0;
    }

    int pivot = (n % 2 == 0)? (n/2) - 1: (n/2);

    //printf("%d\n", pivot);

    int counter = (n % 2 == 0)? (n/2): (n/2) + 1;

    //printf("%d\n", counter);

    for(int i = 0; i < counter; i++){

        printf("%d %d ", n - i, pivot - i);

    }

    if(n % 2 == 0)
        printf("%d", pivot+1);

    printf("\n");


    return 0;

}
