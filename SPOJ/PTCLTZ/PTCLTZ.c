#include<stdio.h>

void whatever(int s, int n){

    if(s == 1){
        printf("%d\n", n);
    }
    else{

        if(s % 2 == 1){

            n++;
            s = s*3 + 1;
            //printf("n:%d s:%d\n", n ,s);
            whatever(s, n);

        }
        else if(s % 2 == 0){

            n++;
            s = s / 2;
            //printf("n:%d s:%d\n", n ,s);
            whatever(s, n);

        }

    }

}

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        int s;

        scanf("%d", &s);

        whatever(s, 0);

    }

    return 0;

}
