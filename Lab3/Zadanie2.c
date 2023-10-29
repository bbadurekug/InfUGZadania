#include<stdio.h>

int main(){

int a, b;
int wynik_dodawania, wynik_odejmowania, wynik_mnozenia, wynik_dzielenia, wynik_reszty;

printf("Podaj dwie liczby: \n");
scanf("%d", &a);
scanf("%d", &b);

wynik_dodawania = a + b;
wynik_odejmowania = a - b;
wynik_mnozenia = a * b;
wynik_dzielenia = a / b;
wynik_reszty = a % b;

printf("Wynik dodawania: %d \n", wynik_dodawania);
printf("Wynik odejmowania: %d \n", wynik_odejmowania);
printf("Wynik mnożenia: %d \n", wynik_mnozenia);
printf("Wynik dzielenia: %d \n", wynik_dzielenia);
printf("Wynik reszty z dzielenia: %d \n", wynik_reszty);

}
