#include<stdio.h>

int main(){

        int x = 0xf6af4b31;
        int y;

        /*asm(

                "mov eax,%1;"
                "xor ebx,ebx;"
                "mov ecx,32;"
        "petla:"
                "add eax,eax;"
                "jnc skok;"
                "inc ebx;"
        "skok:"
                "dec ecx;"
                "jnz petla;"
                "mov %0,ebx;"
                : "=r" (y)
                : "r" (x)
                : "eax", "ebx", "ecx"

        );

        asm(

                "mov eax,%1;"
                "xor ebx,ebx;"
                "xor ecx,ecx;"
        "petla:"
                "add eax, eax;"
                "jnc skok;"
                "inc ebx;"
        "skok:"
                "inc ecx;"
                "cmp ecx, 32;"
                "jnz petla;"
                "mov %0,ebx;"
                : "=r" (y)
                : "r" (x)
                : "eax", "ebx", "ecx"

        );


        asm(

                "mov eax,%1;"
                "xor ebx,ebx;"
                "xor ecx,ecx;"
                "xor edx,edx;"
        "petla:"
                "add eax, eax;"
                "jnc skok;"
                "inc ebx;"
                "jmp skok1;"
        "skok:"
                "xor ebx,ebx;"
        "skok1:"
                "cmp edx,ebx;"
                "jae skok2;"
                "mov edx, ebx;"
        "skok2:"
                "inc ecx;"
                "cmp ecx,32;"
                "jb petla;"
                "mov %0,edx;"
                : "=r" (y)
                : "r" (x)
                : "eax", "ebx", "ecx", "edx"

        );*/

        asm(

                "mov eax,%1;"
                "xor ebx,ebx;"
                "xor ecx,ecx;"
                "xor edx,edx;"
        "skok:"
                "add eax, eax;" //sprawdzam pierwsza liczbe
                "jnc skok1;"  //jezeli nie ma jedynki idz do skok - wyzeruj ebx
                "jmp skok2;"
        "skok1:"
                "xor ebx,ebx;"
                "jmp petla;"
        "skok2:"
                "cmp ebx,1;"
                "je skok3;" //jezeli edx jest wiekszy rowny ebx idz do skok2
                "mov ebx, 1;" //jezeli nie wloz wartosc z ebx do edx
                "jmp petla;"
        "skok3:"
                "inc edx;"
        "petla:"
                "inc ecx;"
                "cmp ecx,32;"
                "jb skok;"
                "mov %0,edx;"
                : "=r" (y)
                : "r" (x)
                : "eax", "ebx", "ecx", "edx" //edx przechowuje najwieksza wartosc

        );

        /*ZADANIE DOMOWE:
         *
         * wyznaczy liczbe ciagow '11' w rozwinieciu dwojkowym liczby
         * ile jest par jedynek w liczbie binajrnej
         * przyklad:
         * 110011100011110001
         * 11--11    1111
         *      11    11
         * 6 par
         * (ile jedynek ma po sobie jedynke)
         * treść zadania w treści maila
         * wszystko w mailu wkleić (nie jako załącznik)
         * do nastepnych laboratoriow piatek 23:59 na email piotr.szuca@ug.edu.pl*/

        printf("x=%i y=%i\n", x, y);

        return 0;

}
