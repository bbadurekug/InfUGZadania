#include<stdio.h>

#define DOBA    86400   //doba w sekundach

int ileZjeDoKoncaDoby(int czasGoscia){

    int ileZje = 0, czas = 0;

    if(czasGoscia != 0){
        while(czas < DOBA){

            czas += czasGoscia;
            ileZje++;

        }

        ileZje = (DOBA % czasGoscia != 0)? ileZje - 1: ileZje;
    }

    return ileZje;

}

int ilePotrzebaPudelek(int ileGosci, int ilePudelko){

    unsigned int ilePudelek = 0, czasGoscia;

    for(int i = 0; i < ileGosci; i++){

        scanf("%d", &czasGoscia);
        //printf("%d zje: %d\n", czasGoscia, ileZjeDoKoncaDoby(czasGoscia));
        ilePudelek += ileZjeDoKoncaDoby(czasGoscia);

    }

    ilePudelek = (ilePudelek % ilePudelko == 0)? ilePudelek / ilePudelko: (ilePudelek / ilePudelko) + 1;

    return ilePudelek;

}

int main(){

    unsigned int testy;

    scanf("%d", &testy);

    for(int i = 0; i < testy; i++){

        unsigned int ileGosci,ilePudelko, czasGoscia;

        scanf("%d %d", &ileGosci, &ilePudelko);

        printf("%d\n", ilePotrzebaPudelek(ileGosci, ilePudelko));

    }
}
