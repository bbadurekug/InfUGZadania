#include<stdio.h>

int main(){

    int n,k;
    scanf("%d %d", &n, &k);

    int tab[n];
    for(int i = 0; i < n; i++) scanf("%d", &tab[i]);

    int temp;

    for(int i = 0; i < k; i++){

        temp = tab[0];
        for(int j = 0; j < (n-1); j++) tab[j] = tab[j+1];
        tab[n-1] = temp;
    }

    for(int i = 0; i < n; i++) printf("%d ", tab[i]);

    return 0;

}
