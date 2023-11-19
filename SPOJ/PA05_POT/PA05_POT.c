#include<stdio.h>

int main(){

    unsigned int D, a, b, potega;

    scanf("%d", &D);

    for(int i = 0; i < D; i++){

        scanf("%d %d", &a, &b);

        switch(a % 10){

        case 0:
            printf("0\n");
            break;
        case 1:
            printf("1\n");
            break;
        case 2:
            switch(b % 4){

            case 0:
                printf("6\n");
                break;
            case 1:
                printf("2\n");
                break;
            case 2:
                printf("4\n");
                break;
            case 3:
                printf("8\n");
                break;
            }
            break;
        case 3:
            switch(b % 4){

            case 0:
                printf("1\n");
                break;
            case 1:
                printf("3\n");
                break;
            case 2:
                printf("9\n");
                break;
            case 3:
                printf("7\n");
                break;
            }
            break;
        case 4:
            switch(b % 2){

            case 0:
                printf("6\n");
                break;
            case 1:
                printf("4\n");
                break;
            }
            break;
        case 5:
            printf("5\n");
            break;
        case 6:
            printf("6\n");
            break;
        case 7:
            switch(b % 4){

            case 0:
                printf("1\n");
                break;
            case 1:
                printf("7\n");
                break;
            case 2:
                printf("9\n");
                break;
            case 3:
                printf("3\n");
                break;
            }
            break;
        case 8:
            switch(b % 4){

            case 0:
                printf("6\n");
                break;
            case 1:
                printf("8\n");
                break;
            case 2:
                printf("4\n");
                break;
            case 3:
                printf("2\n");
                break;
            }
            break;
        case 9:
            switch(b % 2){

            case 0:
                printf("1\n");
                break;
            case 1:
                printf("9\n");
                break;
            }
            break;
        }
    }

    return 0;

}
