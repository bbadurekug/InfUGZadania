#include<Windows.h>
#include<stdio.h>
#include<time.h>

int main() {

    HWND console = GetConsoleWindow();
    HDC hdc = GetDC(console);

    int red = 0;
    int green = 250;
    int blue = 0;
    COLORREF zielony = RGB(red, green, blue);

    int x = 100;
    int y = 10;
    int x0 = x;

    srand(time(NULL));


    for(int i = 0; i < 50; i++){

        for(int k = 0; k < 5; k++){

            x0 = x;


            for(int j = 0; j < i*2; j++){

                SetPixel(hdc, x0, y, zielony);

                x0++;
            }

            y++;
        }

        x--;

    }

    red = 150;
    green = 75;

    COLORREF brazowy = RGB(red, green, blue);

    y+=19;
    x+=49;

    for(int o = 0; o < 20; o++){

        x0 = x - 10;

        for(int p = 0; p < 20; p++){

            SetPixel(hdc, x0, y, brazowy);

            x0++;

        }

        y--;

    }


    ReleaseDC(console, hdc);

    printf("\n\n");

    getchar();

    return 0;
}
