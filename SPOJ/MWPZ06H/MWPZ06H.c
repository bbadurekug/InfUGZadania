#include<stdio.h>

int maxElement(int len, int tab[]){

    int max = -1;

    for(int i = 0; i < len; i++){
        if(tab[i] > max)
            max = tab[i];
    }

    return max;

}

void falseSort(int len, int tab[]){

    int temp;
    int counter = 0;

    for(int i = 0; i < len; i++){

        if(tab[i] == maxElement(len, tab)){

            temp = tab[i];

            for(int j = i; j >= 1; j--){

                tab[j] = tab[j-1];

            }

            tab[counter] = temp;

            counter++;
        }

    }

    sort:

    for(int i = counter; i < len; i++){

        if((i+1) < len && tab[i+1] < tab[i]){

            temp = tab[i];
            tab[i] = tab[i+1];
            tab[i+1] = temp;
            goto sort;

        }

    }

}

/*
3
5
1 5 3 4 4
4
4 5 6 7
3
1 1 1
*/

int main(){

    int d;
    scanf("%d", &d);

    for(int i = 0; i < d; i++){

        int n;
        scanf("%d", &n);
        int tab[n];

        for(int j = 0; j < n; j++){
            scanf("%d", &tab[j]);
        }

        falseSort(n, tab);

        for(int j = 0; j < n; j++){
            printf("%d ", tab[j]);
        }

        printf("\n");

    }

    return 0;

}
