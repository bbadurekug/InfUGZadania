#include<stdio.h>
#include<math.h>

int main(){

    int t;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){

        int n;

        scanf("%d", &n);

        int liczby[n];
        float suma = 0;

        for(int j = 0; j < n; j++){

            scanf("%d", &liczby[j]);
            suma += liczby[j];
        }

        suma /= n;

        float najmniejsza = 100;

        int index;

        for(int k = 0; k < n; k++){

            if(fabs(suma - liczby[k]) < najmniejsza){
                najmniejsza = fabs(suma-liczby[k]);
                index = k;
            }

        }

        if(najmniejsza == suma)
            printf("%d\n", suma);
        else
            printf("%d\n", liczby[index]);
    }

    return 0;

}
