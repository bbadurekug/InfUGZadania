#include<stdio.h>
#include<math.h>

int main(){

    int n;

    printf("Podaj rozmiar tablicy trojwymiarowej:\n");
    scanf("%d", &n);

    int tablica3d[n][n][n];

    int rozmiar = (int)pow(n,3);

    int tablica[rozmiar];

    printf("Podaj wartosci elementow tablicy trojwymiarowej:\n");

    for(int i1 = 0; i1 < n; i1++){

        for(int i2 = 0; i2 < n; i2++){

            for(int i3 = 0; i3 < n; i3++){

                printf("%d%d%d ", i1, i2, i3);
                scanf("%d", &tablica3d[i1][i2][i3]);

            }

        }

    }

    printf("\n");

    int pomoc = 0;

    for(int i1 = 0; i1 < n; i1++){

        for(int i2 = 0; i2 < n; i2++){

            for(int i3 = 0; i3 < n; i3++){

                tablica[pomoc] = tablica3d[i1][i2][i3];
                printf("%d%d%d %d\n", i1, i2, i3, tablica[pomoc]);
                pomoc++;

            }

        }

    }


    return 0;

}
