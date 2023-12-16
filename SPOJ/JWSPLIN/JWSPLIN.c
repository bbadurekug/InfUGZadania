#include<stdio.h>

float m(float x1, float y1, float x2, float y2){

    return (y2 - y1) / (x2 - x1);


}

int main(){

    int d;
    scanf("%d", &d);

    for(int i = 0; i < d; i++){

        float xA, yA, xB, yB, xC, yC;

        scanf("%f %f %f %f %f %f", &xA, &yA, &xB, &yB, &xC, &yC);

        if(xA == xB && xB == xC && xC == xA)
        {
            printf("TAK\n");
        }
        else if(m(xA, yA, xB, yB) == m(xB, yB, xC, yC) &&
                m(xB, yB, xC, yC) == m(xC, yC, xA, yA) &&
                m(xC, yC, xA, yA) == m(xA, yA, xB, yB))
        {
            printf("TAK\n");
        }
        else
            printf("NIE\n");

    }

    return 0;

}
