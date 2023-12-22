#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct punkty{

    int x;
    int y;

} Punkty;

long long int matrix(Punkty a, Punkty b){

    return (((long long int )a.x * (long long int)b.y) - ((long long int)b.x * (long long int)a.y));

}

Punkty *wielokatSzary = NULL;
Punkty *wielokatCzarny = NULL;

int main(){

    int t;
    scanf("%d", &t);

    int size;
    int i;
    int j;
    int activeLoop = 1;

    for(int n = 0; n < t; n++){

        size = 2;
        wielokatCzarny = malloc(sizeof(Punkty) * size);
        i = 0;
        activeLoop = 1;

        while(activeLoop){
            //printf("%d\n", i);
            scanf("%d %d", &wielokatCzarny[i].x, &wielokatCzarny[i].y);
            //printf("%d %d a %d %d\n", wielokatCzarny[i].x, wielokatCzarny[i].y, wielokatCzarny[0].x, wielokatCzarny[0].y);

            if((i > 0) && (wielokatCzarny[i].x == wielokatCzarny[0].x && wielokatCzarny[i].y == wielokatCzarny[0].y))
                activeLoop = 0;

            i++;

            if((i-1) == size){
                size += 2;
                wielokatCzarny = realloc(wielokatCzarny, sizeof(Punkty) * size);
            }

        }
        /*printf("kule ");
        for(int o = 0; o < i; o++) printf("%d %d ", wielokatCzarny[o].x, wielokatCzarny[o].y);
        printf("\n");*/

        size = 2;
        wielokatSzary = malloc(sizeof(Punkty) * size);
        j = 0;
        activeLoop = 1;

        while(activeLoop){
            //printf("%d\n", j);
            scanf("%d %d", &wielokatSzary[j].x, &wielokatSzary[j].y);
            //printf("%d %d a %d %d\n", wielokatSzary[j].x, wielokatSzary[j].y, wielokatSzary[0].x, wielokatSzary[0].y);


            if((j > 0) && (wielokatSzary[j].x == wielokatSzary[0].x && wielokatSzary[j].y == wielokatSzary[0].y))
                activeLoop = 0;

            j++;

            if((j-1) == size){
                size += 2;
                wielokatSzary = realloc(wielokatSzary, sizeof(Punkty) * size);
            }


        }

        /*printf("kule2");
        for(int o = 0; o < j; o++) printf("%d %d ", wielokatSzary[o].x, wielokatSzary[o].y);
        printf("\n");*/

        //printf("i:%d j:%d\n", i, j);

        getchar();

        double poleSzary = 0;
        double poleCzarny = 0;

        for(int m = 0; m < (i - 1); m++){
            poleCzarny += matrix(wielokatCzarny[m], wielokatCzarny[m+1]);
            //printf("biore: %d %d i %d %d\n", wielokatCzarny[m].x, wielokatCzarny[m].y, wielokatCzarny[m+1].x, wielokatCzarny[m+1].y);
            //printf("%f %d %d\n", poleCzarny, matrix(wielokatCzarny[m], wielokatCzarny[m+1]), m);
        }

        if(poleCzarny < 0)
            poleCzarny *= -1.0;

        poleCzarny /= 2.0;

        //printf("Pole czarny %lf\n", poleCzarny);

        for(int n = 0; n < (j - 1); n++){
            poleSzary += matrix(wielokatSzary[n], wielokatSzary[n+1]);
            //printf("biore: %d %d i %d %d\n", wielokatSzary[n].x, wielokatSzary[n].y, wielokatSzary[n+1].x, wielokatSzary[n+1].y);
            //printf("%f %lld %d\n", poleSzary, matrix(wielokatSzary[n], wielokatSzary[n+1]), n);
        }

        if(poleSzary < 0)
            poleSzary *= -1.0;

        poleSzary /= 2.0;

        //printf("Pole szary %lf\n", poleSzary);

        if(poleCzarny > poleSzary || poleSzary == 0){

            double temp = poleSzary;
            poleSzary = poleCzarny;
            poleCzarny = temp;

        }

        poleSzary -= poleCzarny;

        long long int bitokule = poleCzarny * 10.0 + poleSzary * 6.0;

        printf("%lld\n", bitokule);

        free(wielokatSzary);
        free(wielokatCzarny);

    }


    return 0;

}
