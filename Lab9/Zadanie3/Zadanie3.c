#include<stdio.h>
#include<math.h>

struct punkt {

    float x;
    float y;

};

struct trojkat {

    struct punkt p1;
    struct punkt p2;
    struct punkt p3;

};

float odcinki(struct punkt a, struct punkt b){

    float wynik = (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);

    return sqrt(wynik);

}

int czyMozliwyTrojkat(float a, float b, float c){

    if((a + b <= c) && (b + c <= a) && (c + a <= b))
        return 0;

    return 1;

}

int main(){

    struct trojkat trojkat1;

    printf("Podaj punkty trojkata:\n");
    printf("p1:\n");
    scanf("%f %f", &trojkat1.p1.x, &trojkat1.p1.y);
    printf("p2:\n");
    scanf("%f %f", &trojkat1.p2.x, &trojkat1.p2.y);
    printf("p3:\n");
    scanf("%f %f", &trojkat1.p3.x, &trojkat1.p3.y);

    printf("Twoje punkty:\np1: %f %f\np2: %f %f\n p3: %f %f\n", trojkat1.p1.x, trojkat1.p1.y, trojkat1.p2.x, trojkat1.p2.y, trojkat1.p3.x, trojkat1.p3.y);

    if(czyMozliwyTrojkat(odcinki(trojkat1.p1, trojkat1.p2), odcinki(trojkat1.p2, trojkat1.p3), odcinki(trojkat1.p3, trojkat1.p1)))
        printf("Taki trojkat jest mozliwy\n");
    else
        printf("Taki trojkat jest niemozliwy\n");


    return 0;

}
