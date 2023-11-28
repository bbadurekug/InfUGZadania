#include<stdio.h>

int nwd(int a, int b){

    if(b > a){
        b += a;
        a = b - a;
        b -= a;
    }
    if(a == b)
        return a;
    else
        return nwd(a-b, b);

}

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        int a,b;

        scanf("%d %d", &a, &b);

        printf("%d\n", nwd(a,b)*2);

    }

    return 0;
}
