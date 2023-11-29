#include<stdio.h>
#include<stdlib.h>

int main(){

    int data;
    int temp = 0;
    char n[5];

    while(fgets(n, sizeof n, stdin) != NULL) {
        if (sscanf(n, "%d", &data) != 1) break;

        temp += atoi(n);
        printf("%d\n", temp);

    }

    return 0;

}
