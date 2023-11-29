#include<stdio.h>

int newton(int n, int k){

    long long int licznik = 1;

    if(k > n/2)
        k = n-k;

    /*for(int i = 0; i < k; i++){

        licznik = (licznik * (n-i)) / (i+1);

    }*/

    for(int i = 1; i <= k; i++){

        licznik = (licznik * (n - i + 1)) / i;

    }

    return licznik;

}

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        int n, k;

        scanf("%d %d", &n, &k);

        printf("%d\n", newton(n,k));

    }

    return 0;

}
