#include<stdio.h>

int main(){

    float a,b,c,x;
    scanf("%f %f %f", &a, &b, &c);

    if(a == 0 && b == c){
        printf("NWR\n");
        return 0;
    }
    else if(a == 0 && b != c){
        printf("BR\n");
        return 0;
    }

    x = (c - b) / a;

    int balls = x * 100.0;

    printf("%d\n", balls);

    //if(balls % 10 >= 5)
     //   x += 0.01;

    printf("%.2f\n", x);


    return 0;

}
