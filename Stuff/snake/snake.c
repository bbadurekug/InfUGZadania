#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct gameObject{

    int x;
    int y;
    COLORREF color;
    short direction;

}GameObject;

void drawRect(HDC hdc, int x, int y, COLORREF color, int size){

    for(int i = 0; i < size+1; i++){

        for(int j = 0; j < size+1; j++){

            SetPixel(hdc, x+i, y+j, color);

        }

    }

}

int main(){

    HWND console = GetConsoleWindow();
    HDC hdc = GetDC(console);

    COLORREF white = RGB(255,255,255);

    srand(time(NULL));

    short run = 1;

    GameObject player;

    player.x = 50;
    player.y = 50;
    player.color = RGB(0,255,0);

    int tailSize = 1;

    GameObject *tail = malloc(sizeof(GameObject) * tailSize);

    GameObject fruit;

    fruit.x = ((rand() % 19) + 1) * 10;
    fruit.y = ((rand() % 19) + 1) * 10;
    fruit.color = RGB(255,0,0);

    while(run){

        drawRect(hdc, player.x, player.y, player.color, 10);
        drawRect(hdc, fruit.x, fruit.y, fruit.color, 10);
        for(int i = 0; i < tailSize; i++){

            if((tail[i].x != 0 && tail[i].y != 0))
                drawRect(hdc, tail[i].x, tail[i].y, white, 10);

        }

        if((GetAsyncKeyState('W') & 0x8001) && player.direction != 3)
            player.direction = 1;
        else if((GetAsyncKeyState('S') & 0x8001) && player.direction != 1)
            player.direction = 3;
        else if((GetAsyncKeyState('D') & 0x8001) && player.direction != 0)
            player.direction = 2;
        else if((GetAsyncKeyState('A') & 0x8001) && player.direction != 2)
            player.direction = 0;

        if(GetAsyncKeyState('F') & 0x8001){
            tailSize++;
            tail = realloc(tail, sizeof(GameObject) * tailSize);
        }

        if((GetAsyncKeyState('Q') & 0x8001))
            run = 0;

        Sleep(200);
        system("cls");

        for(int i = tailSize-1; i >= 1; i--){

            tail[i].x = tail[i-1].x;
            tail[i].y = tail[i-1].y;
            if(player.x == tail[i].x && player.y == tail[i].y){
                printf("Gracz sprobowal zjesc swoj wlasny ogon! Wynik: %d punktow!", tailSize);
                run = 0;
            }
        }

        tail[0].x = player.x;
        tail[0].y = player.y;

        switch(player.direction){

            case 0:
                player.x -= 10;
                break;
            case 1:
                player.y -= 10;
                break;
            case 2:
                player.x += 10;
                break;
            case 3:
                player.y += 10;
                break;

        }

        if(player.x == fruit.x && player.y == fruit.y){
            fruit.x = ((rand() % 19) + 1) * 10;
            fruit.y = ((rand() % 19) + 1) * 10;
            tailSize++;
            tail = realloc(tail, sizeof(GameObject) * tailSize);
        }

    }

    free(tail);

    Sleep(3000);

    ReleaseDC(console, hdc);

    return 0;

}
