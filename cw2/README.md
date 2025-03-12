## Autor: Jakub Kurek

### Data: 12-03-2025

# Co zawiera

Folder zawiera pliki:
- README - informacje o programach i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- odp.md - Odpowiedź na pytanie ile procesów powstanie po n krotnym wywołaniu funkcji fork() wraz execl().
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:
- cw2.c - kod źródłowy głownego programu
- porcess_info.c - kod źródłowy do programu wypisującego informacje o procesie.

# Do czego służy

Program cw2.x tworzy 3 procesy potomne, które wykonują program podany jako parametry przy wywoływaniu go.

# Jak uruchomić program

Program można uruchomić przy użyciu polecenia
```bash
make run # uruchamia program z cw wraz z parametrem, którym jest ścieżka do programu wypisującego informacje o procesie potomnym
```
lub poprzez wykonanie odpowiedniego pliku z katalogu `./target/exe/cw2.x ./sciezka/do/programu/do/wykonania` po skompilowaniu wszystkich programów przy użyciu polecenia `make all`

# Po zakończeniu

Wszystkie skompilowane pliki można usunąć przy uzyciu polecenia:
```bash
make clean
```
Jeśli chcemy zarchiwizować kod źródłowy można to osiągnąć używając polecenia:
```bash
make tar
```