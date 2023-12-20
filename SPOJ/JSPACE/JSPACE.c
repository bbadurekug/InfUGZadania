#include<stdio.h>

int main(){

    char buffer[10000];

    while(gets(buffer) != NULL){

        int i = 0;

        while(buffer[i] != '\0' && buffer[i] != '\n'){

            if(buffer[i] == ' '){

                if(buffer[i + 1] >= 97 && buffer[i + 1] <= 122)
                    buffer[i + 1] -= 32;

                int j = i;
                while(buffer[j] != '\0' && buffer[j] != '\n'){
                    buffer[j] = buffer[j+1];
                    j++;
                }

                i--;

            }

            i++;

        }

        printf("%s\n", buffer);

    }

    return 0;

}
