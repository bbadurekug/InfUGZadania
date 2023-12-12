#include<stdio.h>

int main(){

    int d;
    scanf("%d", &d);

    for(int i = 0; i < d; i++){

        int l, c;

        scanf("%d %d", &l, &c);

        l -= 1;

        if(l != 0 && c % l != 0)
            printf("TAK\n");
        else if (l == 0 && c != 0)
            printf("TAK\n");
        else
            printf("NIE\n");


    }

    return 0;

}
