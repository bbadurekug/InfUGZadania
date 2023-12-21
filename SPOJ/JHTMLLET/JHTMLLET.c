#include<stdio.h>

int main(){

    char buffer[10000];

    while(gets(buffer) != NULL){

        int i = 0;
        while(buffer[i] != '\0' && buffer[i] != '\n'){

            if(buffer[i] == '<'){

                while(buffer[i] != '>'){

                    if(buffer[i] >= 97 && buffer[i] <= 122)
                        buffer[i] -= 32;

                    i++;

                }

            }

            i++;
        }
        printf("%s\n", buffer);

    }


    return 0;

}
