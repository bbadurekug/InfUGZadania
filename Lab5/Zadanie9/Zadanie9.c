#include<stdio.h>

int przestepny(int rok){

    if(rok % 4 == 0 && rok % 100 != 0){

        printf("Rok %d jest przestepny.\n", rok);

    }
    else if(rok % 400 == 0){

        printf("Rok %d jest przestepny.\n", rok);

    }
    else{

        printf("Rok %d nie jest przestepny.\n", rok);

    }

}

int main(){

    int rok;

    printf("Podaj rok:\n");

    while(rok < 1){
        scanf("%d", &rok);
        if(rok < 1)
            printf("To nie jest poprawny rok. Sprobuj ponownie.\n");
    }

    przestepny(rok);

    return 0;

}
