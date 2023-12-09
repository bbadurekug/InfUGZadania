#include<stdio.h>

int main(){

    int d;

    scanf("%d", &d);

    for(int i = 0; i < d; i++){

        int n;

        scanf("%d", &n);

        printf("%d\n", n*n);

    }

    return 0;

}
