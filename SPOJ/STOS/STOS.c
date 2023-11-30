#include<stdio.h>
#include<stdlib.h>

int main(){

    int data;
    char znak;
    char n[5];

    int i = 0;
    int arr[10];

    int toArr = 0;

    while(fgets(n, sizeof n, stdin) != NULL) {

        if(n[0] == '\n')
            break;

        if(sscanf(n, "%d", &data) == 1){

            if(toArr == 1){

                arr[i] = data;
                i++;
                toArr--;
                printf(":)\n");

            }
            else
                printf(":(\n");

        }

        else if(sscanf(n, "%c", &znak) == 1){

            switch(znak){

                case '+':
                    if(i < 10){

                        //printf(":)\n");
                        toArr++;

                    }
                    break;

                case '-':
                    if(i > 0){

                        printf("%d\n", arr[i-1]);
                        i--;

                    }
                    else
                        printf(":(\n");
                    break;

            }

        }

        else
            break;


        //printf("%d\n", data);

        //printf("%c\n", znak);
    }

    return 0;

}
