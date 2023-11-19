#include<stdio.h>

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

    int suma = a + b + c;

    if(suma - najdluzsza(a,b,c) > najdluzsza(a,b,c)){

        printf("Z tych dlugosci moze powstac trojkat!");
    }
    else{

        printf("Z tych dlugosci NIE moze powstac trojkat!");
    }

    return 0;

}
