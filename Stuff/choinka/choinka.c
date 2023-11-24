#include<Windows.h>
#include<stdio.h>
#include<time.h>

int main() {

    HWND console = GetConsoleWindow();
    HDC hdc = GetDC(console);

    int red = 0;
    int green = 100;
    int blue = 20;

    int x = 500;
    int y = 10;
    int x0 = x;

    srand(time(NULL));

    COLORREF bialy = RGB(255,255,255);

    int wysokosc = 75 + (rand()%51);

    for(int i = 0; i < wysokosc; i++){

        for(int k = 0; k < 5; k++){

            x0 = x;


            for(int j = 0; j < i*2; j++){

                if(rand() % 10 == 0)
                    SetPixel(hdc, x0, y, bialy);
                else{
                    green = 50 + (rand()%75);

                    COLORREF zielony = RGB(red, green, blue);

                    SetPixel(hdc, x0, y, zielony);
                }

                x0++;
            }

            y++;
        }

        x--;

    }

    COLORREF ciemnyBrazowy = RGB(90, 60, 50);

    COLORREF brazowy = RGB(127,81,18);

    int wysokoscPnia = wysokosc/3;

    y+=wysokoscPnia-1;
    x+=wysokosc-1;

    for(int o = 0; o < wysokoscPnia; o++){

        x0 = x - (wysokoscPnia/2);

        for(int p = 0; p < wysokoscPnia; p++){

            if(rand() % 4 == 0)
                SetPixel(hdc, x0, y, ciemnyBrazowy);
            else
                SetPixel(hdc, x0, y, brazowy);

            x0++;

        }

        y--;

    }


    ReleaseDC(console, hdc);

    getchar();

    return 0;
}
