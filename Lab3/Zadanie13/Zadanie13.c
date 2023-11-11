#include<stdio.h>

int main(){

    printf("Dla 0 radianów wybierz 1\n");
    printf("Dla 1/6 Pi rad wybierz 2\n");
    printf("Dla 1/4 Pi rad wybierz 3\n");
    printf("Dla 1/3 Pi rad wybierz 4\n");
    printf("Dla 1/2 Pi rad wybierz 5\n");

    short menu;

    scanf("%d", &menu);

    switch(menu){
        case 1:
            printf("0\n");
            printf("0 radianow to %d stopni.\n", 0);
            break;
        case 2:
            printf("1/6 Pi\n");
            printf("1/6 Pi radianow to %d stopni.\n", 180/6);
            break;
        case 3:
            printf("1/4 Pi\n");
            printf("1/4 Pi radianow to %d stopni.\n", 180/4);
            break;
        case 4:
            printf("1/3 Pi\n");
            printf("1/3 Pi radianow to %d stopni.\n", 180/3);
            break;
        case 5:
            printf("1/2 Pi\n");
            printf("1/2 Pi radianow to %d stopni.\n", 180/2);
            break;
    }

    return 0;

}
