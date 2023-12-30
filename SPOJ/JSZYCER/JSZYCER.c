#include<stdio.h>
#include<stdlib.h>

int main(){

    char *input = malloc(sizeof(char) * 201);

    int i;

    while(fgets(input, sizeof(input), stdin) != NULL){

        i = 0;

        while(input[i] != 0){

            if(input[i] >= 65 && input[i] <= 90){
                input[i] += 3;

                if(input[i] > 90)
                    input[i] -= 26;

             }

            i++;
        }

        printf("%s", input);

    }

    free(input);

    return 0;

}
