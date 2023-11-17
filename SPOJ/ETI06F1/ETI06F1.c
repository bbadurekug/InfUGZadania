#include<stdio.h>
#include<math.h>

#define PI 3.141592654

int main(){

    double r,d;

    scanf("%lf", &r);
    scanf("%lf", &d);

    double polowaD = d/2.0;

    double polowaPodstawyTrojkata, poleTrojkata, poleKola;

    polowaPodstawyTrojkata = sqrt(r * r - polowaD * polowaD);

    poleKola = PI * polowaPodstawyTrojkata * polowaPodstawyTrojkata;

    printf("%.2lf", poleKola);

    return 0;

}
