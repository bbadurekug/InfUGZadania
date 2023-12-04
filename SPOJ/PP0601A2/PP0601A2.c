#include<stdio.h>

int main(){

    int counter = 0;
    int prev = 42;

    while(counter != 3){

        int n;
        scanf("%d", &n);
        if(n==42 && n != prev)
            counter++;
        printf("%d\n", n);
        prev = n;
    }

    return 0;

}
