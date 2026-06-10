### Opis programu

Zadaniem programu jest znalezienie słowa kluczowego w danym pliku. Na wejściu program oczekuje ścieżki do instiejącego pliku, do którego program ma dostęp i zawiera conajmniej tyle znaków, żeby można było go podzielić na daną liczbę procesów.

Jeżeli ścieżka do pliku lub klucz nie zostaną podane podczas wywołania programu, użytkownik będzie miał możliwość podania ich w trakcie działania programu.

Po weryfikacji podanego pliku, program przedstawia użytkownikowi menu wyboru. Program implementuje 3 algorytmu szukania wzorca w tekscie:
1. Brute force - naiwne przeszukiwanie pliku znak po znaku
2. Boyer-Moore - implementacja algorytmu Boyer-Moore w wariancie Horspoola używa słownika `bad_match_table`
3. Knuth-Morris-Pratt - używa tabeli `longest_prefix_table` w celu zmiejszenia liczby porównań znaków

W menu istnieje również możliwość zakończenia działania programu wybierając liczbę `9`. Jeżeli podany przez użytkownika wybór nie znajduje się w liście, program prosi o ponowną próbę wyboru.

Po poprawnym wyborze program dzieli plik na odpowiednie zakresy. Każdy proces otrzymuje dokładnie jeden zakres (łącznie z procesem 0). Zakresy są wyznaczane w taki sposób, aby klucze znajdujące się na krańcach zakresów również mogły być znalezione.

Następnie, w zależności do wymagań algorytmu, program przygotowuje się do wykonania go przez np. stworzenie `bad_match_table` dla algorytmu BM lub `longest_prefix_table` dla KMP.

Ostatecznie, program wykonuje wybrany przez użytkownika algorytm i zbiera wyniki, które wyświela w konsoli.

### Uruchamianie programu

Program  uruchamiamy za pomocą menadżera procesów 'mpirun' lub 'mpiexec':

```bash
mpirun -n <liczba_procesów> python3 zadanie_wspolbieznosc_blazej_badurek_292517.py <ścieżka_do_pliku> <szukany_klucz> [flagi]
```

Przykład użycia:
```bash
mpirun -n 3 python3 zadanie_wspolbieznosc_blazej_badurek_292517.py ./text.txt lorem -s
```

#### Uwaga
Jeżeli chcemy uruchomić program z większą liczbą procesów, niż dostępna liczba rdzeni w procesorze, powinnyśmy użyc flagi `--oversubscribe`

Np.
```bash
mpirun --oversubscribe -n 8 python3 zadanie_wspolbieznosc_blazej_badurek_292517.py ./text.txt lorem 
``` 

### Testy

W ramach programu zostały również przygotowane zautomatyzowane testy CLI. Wystarczy odpalić je komendą (znajdując się w katalogu głównym):

```bash
python3 tests/test.py
```

### Flagi

Zdefiniowane zostały następujące flagi. Wszystkie można podjrzeć w konsoli używając flagi `-h` lub `--help`:

Np.
```bash
mpirun -n 3 python3 zadanie_wspolbieznosc_blazej_badurek_292517.py ./text.txt lorem -h
```

* `-r`, `--race` - Tryb wyścigu. Pierszy proces, który znajdzie klucz w pliku, ogłasza swoje ID i indeks znaleznionego klucza. Program kończy działanie po pierwszym znalezionym kluczu.
* `-s`, `--stats` - Program wyświetla statystyki początkowe i końcowe zawierające m.in. informacje o pliku i kluczu oraz czas wykonywania algorytmu.
* `-f`, `--finds` - Program wyśwtiela w konsoli komunikat, gdy jeden z procesów znajdzie klucz.
* `-c`, `--checks` - Program wyświetla w konsoli komunikat, jaki aktualnie znak proces sprawdza i ile znaków w ciągu już pasuje do klucza.
* `-n`, `--keep-newlines` - Program nie ignoruje znaku nowej linii. Jeżeli poszukiwane słowo jest oddzielone znakiem nowej linii np. lor\nem, nie zostanie znaleziony przez algorytm w tej wersji programu.
* `-i`, `--ignore-case` - Program ignoruje wielkość liter podczas wyszukiwania słowa kluczowego, np. LoREm = lorem.  
