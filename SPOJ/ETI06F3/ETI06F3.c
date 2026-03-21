#include<stdio.h>
#include<stdlib.h>

int pierwszyNiewybrany(int n, int tab[]){

    for(int i = 0; i < n; i++)
        if(tab[i] == 0) return i;

    return -1;
}

int rosnaco(const void * a, const void * b){

    int _a = *(int*)a;
    int _b = *(int*)b;

    if(_a < _b)
        return -1;
    else if (_a > _b)
        return 1;
    else
        return 0;

}

int main(){

    int n;
    scanf("%d", &n);

    int uczniowie[n][n];

    for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){

            scanf("%d", &uczniowie[i][j]);

        }


    }

    //printf("\n");

    /*for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){

            printf("%d ", uczniowie[i][j]);

        }

        printf("\n");

    }*/

    int juzWDruzynie[n];

    for(int i = 0; i < n; i++)
        juzWDruzynie[i] = 0;

    int druzyny[3] = {0};
    int d = 0;
    int i = 0;

    while(pierwszyNiewybrany(n, juzWDruzynie) != -1){

        i = pierwszyNiewybrany(n, juzWDruzynie);
        //printf("pnw: %d %d\n", pierwszyNiewybrany(n, juzWDruzynie), d);

        if(d > 2){
            printf("NIE\n");
            return 0;
        }
        else if(druzyny[d] == 0)
            druzyny[d]++;

        juzWDruzynie[i] = 1;
        int rowne = 0;

        for(int j = 0; j < n; j++){

            if(juzWDruzynie[j] == 0 && i != j){

                for(int k = 0; k < n; k++){

                    //printf("Porownuje: uczniowie %d i  uczniowie %d\n", i, j);

                    if(uczniowie[i][k] == uczniowie[j][k])
                        rowne++;

                }

                if(rowne == n){

                    //printf("Match: uczniowie %d i uczniowie %d\n", i, j);
                    druzyny[d]++;
                    juzWDruzynie[j] = 1;
                }

                rowne = 0;
            }

        }

        //printf("Jestem na: %d, druzyny %d %d %d\n", d, druzyny[0], druzyny[1], druzyny[2]);

        d++;

    }

    if(d < 3){
        printf("NIE");
        return 0;
    }
    else{
        qsort(druzyny, 3, sizeof(int), rosnaco);
        printf("TAK %d %d %d", druzyny[0], druzyny[1], druzyny[2]);
    }

    return 0;

}
