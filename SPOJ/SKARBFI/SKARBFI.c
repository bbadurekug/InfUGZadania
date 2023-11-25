#include<stdio.h>
#include<math.h>

int main(){

    int d = 0;

    scanf("%d", &d);

    for(int i = 0; i < d; i++){

        int n;
        int x = 0,y = 0;

        scanf("%d", &n);

        for(int j = 0; j < n; j++){

            int kierunek, kroki;

            scanf("%d %d", &kierunek, &kroki);

            //polnoc +y
            //polodnie -y
            //zachod -x
            //wschod +x

            switch(kierunek){
                case 0:
                    y += kroki;
                    break;
                case 1:
                    y -= kroki;
                    break;
                case 2:
                    x -= kroki;
                    break;
                case 3:
                    x += kroki;
                    break;
            }

        }

        if(y == 0 && x == 0)
        {
            printf("studia\n");
        }
        else{
            if(y > 0)
                printf("0 %d\n", y);
            else if(y < 0)
                printf("1 %d\n", abs(y));
            if(x > 0)
                printf("3 %d\n", x);
            else if(x < 0)
                printf("2 %d\n", abs(x));
        }


        x = 0;
        y = 0;

    }

    return 0;

}
