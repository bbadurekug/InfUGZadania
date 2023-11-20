#include<stdio.h>

int przestepny(int rok){

    if(rok % 4 == 0 && rok % 100 != 0){

        return 1;

    }
    else if(rok % 400 == 0){

        return 1;

    }
    else{

        return 0;

    }

}

int main(){

    int miesiac, rok;

    printf("Podaj miesiac i rok oddzielone spacja (miesiac jako liczba):\n");
    scanf("%d %d", &miesiac, &rok);

    if(miesiac == 2){
        if(przestepny(rok))
            printf("%d", 29);
        else
            printf("%d", 28);
    }
    else if((miesiac<8 && miesiac%2==1) || (miesiac>=8 && miesiac%2==0))
        printf("%d", 31);
    else
        printf("%d", 30);

    //(miesiac<8 && miesiac%2==1) dni 31 tez (miesiac>=8 && miesiac%2==0)
    //(miesiac<8 && miesiac%2==0) 30 lub mniej (miesiac>=8 && miesiac%2==1)

    return 0;

}
