## Autor: Jakub Kurek

### Data: DD-MM-RRRR

# Co zawiera

Folder zawiera pliki:
- README - informacje o programach i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- odp.md - Odpowiedź na pytanie ile procesów powstanie po n krotnym wywołaniu funkcji fork() wraz execl().
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:
- prod_con_manager.c
- producer.c
- consumer.c

# Do czego służy
- prod_con_manager.x - przyjmuje nazwę potoku oraz nazwy plików. Tworzy nazwany potok. Następnie tworzy 2 proesy potomne z programami podanymi jako parametry, które otrzymują potok oraz pliki do zapisu/odczytu
- producer.x - odczytuje dane z podanego pliku i wysyła je do nazwanego potoku.
- consumer.x - przyjmuje dane z potoku a następnie zapisuje je do pliku

# Jak uruchomić program
```bash
make runa # Uruchamia program, który tworzy potok i procesy potomne
make runb # Tworzy potok z poziomu terminala. Tworzy 2 nowe terminale, w których uruchhamia producenta i konsumenta. Po zakończeniu usuwa potok.
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