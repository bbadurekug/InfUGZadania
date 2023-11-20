/*
    Program przyjmuje 'n' liczb i wypisuje je od tylu.
    Program wspiera zarowno liczby ujemne jak i wielocyfrowe.
    Jedynym ograniczeniem jest wielkosc zmiennych.
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(){

    int n = 0, temp = 0, znaki = 0, dlugosc = 0;
    unsigned long long int liczby = 0;

    printf("Ile liczb calkowitych chcesz podac?:\n");
    scanf("%d", &n);

    printf("Podaj %d liczb:\n", n);

    for(int i = 0; i < n; i++){

        scanf("%d", &temp);

        //Przechowuje wpisane liczby w 'temp'

        if(temp)
            dlugosc = dlugosc * 10 + (log10(llabs(temp)) + 1);
        else
            dlugosc *= 10;

        //Jezeli n=0, to dlugosc tez 0, inaczej wpisuje dlugosc liczby
        //Bez tego program crashowal, jezeli 0 bylo ostatnie

        if(temp < 0){
            liczby = (liczby * (unsigned long long int)pow(10, dlugosc % 10)) + llabs(temp);
            znaki = znaki * 10 + 2;
        }
        else{
            liczby = (liczby * (unsigned long long int)pow(10, dlugosc % 10)) + temp;
            znaki = znaki * 10 + 1;
        }

        //Wpisuje liczbe z 'temp' do 'liczby'
        //Jezeli n>0, wpisuje 1 do 'znaki', w przeciwnym wypadku wpisuje 2 do 'znaki'

    }

    printf("Twoje liczby od tylu:\n");

    int ileModulo, ilePodzielic;

    for(int j = 0; j < n; j++){

        ilePodzielic = 0;
        ileModulo = 0;

        for(int k = 0; k < j; k++){

            ilePodzielic += (dlugosc % (int)pow(10, k+1)) / (int)pow(10, k);

            //Oblicza do ktorej potegi 10 trzeba podzielic reszte 'liczby', aby dostac porzadana liczbe

        }

        for(int k = 0; k < (j+1); k++){

            ileModulo += (dlugosc % (int)pow(10, k+1)) / (int)pow(10, k);
            //Oblicza do ktorej potegi 10 trzeba obliczyc reszte z dzielenia calosci 'liczby', aby dostac porzadana liczbe

        }

        if((znaki % (unsigned long long int)pow(10, j+1)) / (unsigned long long int)pow(10, j) == 2)
            printf("-");

        //Jezeli liczba ujemna, wypisuje '-' przed

        printf("%d ", (liczby % (unsigned long long int)pow(10, ileModulo)) / (unsigned long long int)pow(10, ilePodzielic));

    }

    return 0;

}
