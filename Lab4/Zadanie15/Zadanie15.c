#include<stdio.h>

int main(){

    int n = 0;

    printf("Podaj rozmiar tablicy trojwymiarowej:\n");
    scanf("%d", &n);

    int tablica3d[n][n][n]; /*= { { {1,2,3}, {0,1,2}, {0,0,1} },
                               { {0,0,0}, {0,0,0}, {0,3,0} },
                               { {1,2,3}, {0,1,2}, {0,0,1} }, };*/

    printf("Podaj wartosci elementow tablicy trojwymiarowej:\n");

    for(int i1 = 0; i1 < n; i1++){

        for(int i2 = 0; i2 < n; i2++){

            for(int i3 = 0; i3 < n; i3++){

                printf("%d%d%d ", i1, i2, i3);
                scanf("%d", &tablica3d[i1][i2][i3]);

            }

        }

    }

    printf("\nTwoja trojwymiarowa tablica:\n");

    for(int i1 = 0; i1 < n; i1++){

        for(int i2 = 0; i2 < n; i2++){

            for(int i3 = 0; i3 < n; i3++){

                printf("%d ", tablica3d[i1][i2][i3]);

            }

            printf("\n");

        }

        printf("\n");

    }

    printf("\nElementy wieksze od swoich sasiadow:\n");

    short wiekszy = 0;


    for(int i1 = 0; i1 < n; i1++){

        for(int i2 = 0; i2 < n; i2++){

            for(int i3 = 0; i3 < n; i3++){

                wiekszy = 0;

                if(i1+1 <= n){
                    if(tablica3d[i1][i2][i3] > tablica3d[i1+1][i2][i3]){
                        wiekszy++;
                    }
                    else{
                        wiekszy = wiekszy;
                    }
                }
                else{
                    wiekszy++;
                }

                if(i1-1 >= 0){
                    if(tablica3d[i1][i2][i3] > tablica3d[i1-1][i2][i3]){
                        wiekszy++;
                    }
                    else{
                        wiekszy = wiekszy;
                    }
                }
                else{
                    wiekszy++;
                }

                if(i2+1 <= n){
                    if(tablica3d[i1][i2][i3] > tablica3d[i1][i2+1][i3]){
                        wiekszy++;
                    }
                    else{
                        wiekszy = wiekszy;
                    }
                }
                else{
                    wiekszy++;
                }

                if(i2-1 >= 0){
                    if(tablica3d[i1][i2][i3] > tablica3d[i1][i2-1][i3]){
                        wiekszy++;
                    }
                    else{
                        wiekszy = wiekszy;
                    }
                }
                else{
                    wiekszy++;
                }
                if(i3+1 <= n){
                    if(tablica3d[i1][i2][i3] > tablica3d[i1][i2][i3+1]){
                        wiekszy++;
                    }
                    else{
                        wiekszy = wiekszy;
                    }
                }
                else{
                    wiekszy++;
                }

                if(i3-1 >= 0){
                    if(tablica3d[i1][i2][i3] > tablica3d[i1][i2][i3-1]){
                        wiekszy++;
                    }
                    else{
                        wiekszy = wiekszy;
                    }
                }
                else{
                    wiekszy++;
                }

                if(wiekszy == 6){

                    printf("%d%d%d %d\n", i1, i2, i3, tablica3d[i1][i2][i3]);

                }

            }

        }

    }

    return 0;

}
