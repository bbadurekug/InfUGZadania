#include<stdio.h>

void wieksze_od_sasiadow(int tablica3D[3][3][3]){

    char wiekszy;

    printf("Wieksze od sasiadow:\n");

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){

                if(i+1 < 3){
                    if(tablica3D[i][j][k] > tablica3D[i+1][j][k])
                        wiekszy++;
                }
                else
                    wiekszy++;

                if(i-1 >= 0){
                    if(tablica3D[i][j][k] > tablica3D[i-1][j][k])
                        wiekszy++;
                }
                else
                    wiekszy++;

                if(j+1 < 3){
                    if(tablica3D[i][j][k] > tablica3D[i][j+1][k])
                        wiekszy++;
                }
                else
                    wiekszy++;

                if(j-1 >= 0){
                    if(tablica3D[i][j][k] > tablica3D[i][j-1][k])
                        wiekszy++;
                }
                else
                    wiekszy++;

                if(k+1 < 3){
                    if(tablica3D[i][j][k] > tablica3D[i][j][k+1])
                        wiekszy++;
                }
                else
                    wiekszy++;

                if(k-1 >= 3){
                    if(tablica3D[i][j][k] > tablica3D[i][j][k-1])
                        wiekszy++;
                }
                else
                    wiekszy++;

                if(wiekszy == 6)
                    printf("tablica3D[%d][%d][%d] jest wieksza od swoich sasiadow i wynosi %d\n", i,j,k, tablica3D[i][j][k]);
                wiekszy = 0;
            }
        }

    }

}

int main(){

    int rozmiar = 3;

    int tablica3D[3][3][3] = { { {1, 2, 3}, {0, 1, 2}, {0, 0, 1} },
                               { {1, 2, 1}, {2, 3, 2}, {1, 2, 1} },
                               { {1, 2, 3}, {0, 1, 2}, {0, 0, 1} } };

    printf("Twoja talblica:\n\n");

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){

                printf("%d ", tablica3D[i][j][k]);

            }

            printf("\n");

        }

        printf("\n");

    }

    wieksze_od_sasiadow(tablica3D);

    return 0;

}
