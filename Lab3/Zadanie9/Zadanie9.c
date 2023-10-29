#include<stdio.h>
#include<stdlib.h>

int main(){

    int a, b, c, d;

    int bok1, bok2, pole;

    printf("Podaj dwie pary liczb reprezentujących przeciwległe wierzchodzłki prostokąta (w formacie 'a b c d')\n");
    scanf(" %d %d %d %d", &a, &b, &c, &d);

    bok1 = abs(a - c);
    bok2 = abs(b - d);
    pole = bok1 * bok2;

    printf("Długości boków: %d i %d jednostek \n", bok1, bok2);
    printf("Pole: %d jednostek kwadratowych \n", pole);

}
