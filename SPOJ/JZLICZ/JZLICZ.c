#include<stdio.h>
#include<stdlib.h>

int main(){

    int n;
    scanf("%d ", &n);

    static int zliczDuze[26] = {0};
    static int zliczMale[26] = {0};

    for(int i = 0; i < n; i++){

        char slowo[201];
        fgets(slowo, sizeof(slowo), stdin);

        int i = 0;
        while(slowo[i] != '\0' && slowo[i] != '\n'){

            if(slowo[i] >= 65 && slowo[i] <= 90)
                zliczDuze[slowo[i] - 65]++;
            else if(slowo[i] >= 97 && slowo[i] <= 122)
                zliczMale[slowo[i] - 97]++;
            i++;

        }

    }

    for(int i = 0; i < 26; i++){

        if(zliczMale[i] != 0)
            printf("%c %d\n", i + 97, zliczMale[i]);

    }

    for(int i = 0; i < 26; i++){

        if(zliczDuze[i] != 0)
            printf("%c %d\n", i + 65, zliczDuze[i]);

    }

    return 0;

}
