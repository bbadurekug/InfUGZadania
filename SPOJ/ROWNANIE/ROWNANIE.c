#include<stdio.h>
#include<stdlib.h>

int obliczDelta(float a, float b, float c){

    float delta;

    delta = (b * b) - (4 * a * c);

    //printf("delta: %f\n", delta);

    if(delta > 0)
        return 2;
    else if(delta == 0)
        return 1;
    else
        return 0;

}

int main(){

    float data;
    float n[3];
    int i = 0;
    char nChar[100];

    while(fgets(nChar, sizeof(nChar), stdin) != NULL){

        if(sscanf(nChar,"%f %f %f", &n[0], &n[1], &n[2]) != 3)
            break;

        //n[0] = atof(nChar);

        //printf("ny: %f", n[0]);

        //scanf("%f", &n[1]);
        //scanf("%f", &n[2]);

        printf("%d\n", obliczDelta(n[0], n[1], n[2]));

    }



    return 0;

}
