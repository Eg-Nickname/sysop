## Autor: Jakub Kurek

### Data: DD-MM-RRRR

# Co zawiera

Folder zawiera pliki:
- README - informacje o programach i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:
- check_error.h - makra sprawdzajace poprawność wykonanych funkcji bibliotecznych
- consumer.c
- producer.c
- sem_mem_controler.c
- ring_buf.h - deklaracja bufora cyklicznego i funkcji
- ring_buf.c - definicje funkcji pomocniczych bufora cyklicznego
- semaphore.h - deklaracje funkcji pomocniczych semaforów
- semaphore.c - definicje funkcji pomocniczych semaforów
- shared_mem.h - deklaracje funckji pomocniczych pamieci dzielonej
- shared_mem.c - definicje funckji pomocniczych pamici dzielonej


# Do czego służy
Program realizuje problem producenta i konsumenta przy użyciu semaforów, 
pamięci dzielonej i bufora cyklicznego.

- check_error.h
- sem_mem_controler.x -  przyjmuje nazwę smeafora producenta i konsumenta, pamięci dzielonej oraz nazwy plików. Tworzy semafory i pamięć dzielona. Następnie tworzy 2 proesy potomne z programami podanymi jako parametry, które otrzymują semafory, pamięć dzieloną oraz pliki do zapisu/odczytu
- producer.x - odczytuje dane z podanego pliku i wysyła je do bufora cyklicznego w pamięci dzielonej.
- consumer.x - przyjmuje dane z bufora cyklicznego w pamięci dzielonej a następnie zapisuje je do pliku.


# Jak uruchomić program
```bash
make runs # Uruchomienie programu w wersji z biblioteka statyczna
make rund # Uruchomienie programu w wersji z biblioteka dynamiczna
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