#include<stdio.h>

int przekroj_odcinkow(int a1, int b1, int a2, int b2){

    if(a1 < a2 && b1 < b2){
        if(b1 - a2 >= 0)
            return b1;
        else
            return -1;
    }
    else if(a1 > a2 && b1 > b2){
        if(b2 - a1 >= 0)
            return b2;
        else
            return -1;
    }
    else if(a1 < a2 && b1 > b2)
        return b2;
    else if(a1 > a2 && b1 < b2)
        return b1;


}

int main(){

    int a1,b1,a2,b2;

    printf("Podaj cztery liczby naturalne reprezentujace odcinki [a1,b1] i [a2,b2] oddzielone spacja:\n");
    scanf("%d %d %d %d", &a1, &b1, &a2, &b2);

    printf("%d", przekroj_odcinkow(a1,b1,a2,b2));


    return 0;

}
