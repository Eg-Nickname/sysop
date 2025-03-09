## Autor: Jakub Kurek

### Data: 09-03-2025

# Co zawiera

Folder zawiera pliki:
- README - informacje o programach i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- odp.md - Odpowiedź do podpunktu D (rysunek drzewa procesów potomnych) oraz odpowiedź na pytanie ile procesów powstanie po n krotnym wywołaniu funkcji fork().
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:
- cw1a.c - kod źródłowy programu do podpunktu A
- cw1b.c - kod źródłowy programu do podpunktu B
- cw1c.c - kod źródłowy programu do podpunktu C
- cw1d.c - kod źródłowy programu do podpunktu D
- cw1e.c - kod źródłowy programu do podpunktu E
- process_info.h - interfejs współdzielonej funkcji wypisującej informacje o procesie
- process_info.c - implementacja interfejsu z processs_info.h

# Do czego służy

- Program A - Wypisuje informacje o procesie (UID, GID, PID, PPID, PGID)
- Program B - Tworzenie procesów potomnych i wypiswanie informacji o nich jw.
- Program C - Osieracanie procesów potomnych by sprawdzić PID procesu, który je adoptuje w systemie.
- Program D - Wypisanie informacji o procesach jak w programie B, lecz przy użyciu funkcji sleep() ustawienie wypisywania w kolejności od najstarszego pokolenia do najmłodszego pokolenia.
- Program E - Tworzenie oraz zmiana grupy procesów na własną przez procesy potomne 

# Jak uruchomić program

Programy do odpowiednich podpunktów można uruchomić przy użyciu polecenia
```bash
make runa # dla programu z podpunktu a
make runb # dla programu z podpunktu b
make runc # dla programu z podpunktu c
make rund # dla programu z podpunktu d
make rune # dla programu z podpunktu e
```
lub poprzez wykonanie odpowiedniego pliku z katalogu `./target/exe/nazwa_programu.x` po skompilowaniu wszystkich programów przy użyciu polecenia `make all`