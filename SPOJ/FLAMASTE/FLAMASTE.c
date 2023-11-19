#include<stdio.h>

int main(){

    char znaki[201];

    unsigned char ilePodRzad = 1;

    unsigned int C;

    scanf("%d", &C);

    for(int i = 0; i < C; i++){

        scanf("%s", znaki);

        for(int j = 0; j < 201; j++){

            if(znaki[j] < 65 || znaki[j] > 90){

                int k = 0;

                while(k < j){

                    if((k+1 <= j) && (znaki[k] == znaki[k+1])){

                        ilePodRzad++;

                    }
                    else if((k+1 <= j) && (znaki[k] != znaki[k+1])){

                        if(ilePodRzad > 2){
                            printf("%c%d", znaki[k], ilePodRzad);
                            ilePodRzad = 1;
                        }
                        else if(ilePodRzad == 2){
                            printf("%c%c", znaki[k], znaki[k-1]);
                            ilePodRzad = 1;
                        }
                        else{
                            printf("%c", znaki[k]);
                            ilePodRzad = 1;
                        }

                    }

                    k++;

                }

                printf("\n");

                break;

            }

        }

    }

    return 0;

}
