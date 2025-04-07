## Autor: Jakub Kurek

### Data: 01-04-2025

# Co zawiera

Folder zawiera pliki:
- README - informacje o programach i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:
- producer_cosumer.c

# Do czego służy
- producer_consumer.x - program przyjmuje dwie nazwy plików, jeden do odczytu drugi do zapisuj.
Tworzy jeden proces potomny, który przyjmuje dane odczytane z pliku
przekazane przy użyciu potoku. Po odczycie wypsiuje je na standardowe wyjście
oraz zapisuje do pliku podanego jako zapis. Procesy odczytujące i zapisujące
dane posiadają losowy czas uśpienia pomidzy odczytem/zapisem symulujący
przetwarzanie danych

# Jak uruchomić program
```bash
make run READ_FILE=./file_to_read_data WRITE_FILE=./file_to_write_data
```

# Po zakończeniu

Wszystkie skompilowane pliki można usunąć przy uzyciu polecenia:
```bash
make clean
```
Jeśli chcemy zarchiwizować kod źródłowy można to osiągnąć używając polecenia:
```bash
make tar
```