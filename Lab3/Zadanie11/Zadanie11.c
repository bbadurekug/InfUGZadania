#include<stdio.h>
#include<math.h>

int najdluzsza(int a, int b, int c){

    int najdluzsza = 0;

    if((a >= b && a >= c) && a != najdluzsza)
        najdluzsza = a;
    else if((b >= a && b >= c) && b != najdluzsza)
        najdluzsza = b;
    else if((c >= a && c >= b) && c != najdluzsza)
        najdluzsza = c;
    else
        najdluzsza = a;

    return najdluzsza;
}

int main(){

    int a,b,c;

    printf("Podaj trzy dlugosci trzech odcinkow:\n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    int kwadratA, kwadratB, kwadratC;

    kwadratA = (int)pow(a,2);
    kwadratB = (int)pow(b,2);
    kwadratC = (int)pow(c,2);

    int sumaKwadratow = kwadratA + kwadratB + kwadratC;

    if(sumaKwadratow - najdluzsza(kwadratA, kwadratB, kwadratC) == najdluzsza(kwadratA, kwadratB, kwadratC)){

        printf("Z tych dlugosci moze powstac trojkat prostokatny!");
    }
    else{

        printf("Z tych dlugosci NIE moze powstac trojkat prostokatny!");
    }


    return 0;

}
