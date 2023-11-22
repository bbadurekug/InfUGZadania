#include<stdio.h>

#define T_SIZE  1001

int main(){

    int t;

    scanf("%d", &t);

    char s1[T_SIZE], s2[T_SIZE];

    for(int i = 0; i < t; i++){

        scanf("%s %s", s1, s2);

        for(int j = 0; j < T_SIZE; j++){

            if(s1[j] == '\0' || s2[j] == '\0')
                break;

            printf("%c", s1[j]);
            printf("%c", s2[j]);

        }

        printf("\n");
    }

    return 0;

}
