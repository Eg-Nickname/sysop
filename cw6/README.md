## Autor: Jakub Kurek

### Data: 29-04-2025

# Co zawiera

Folder zawiera pliki:
- README - informacje o programach i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:
- sem_controler.c
- sem_user.c
- semaphore.c
- semaphore.h - plik nagłówkowy zawierający deklaracje funkcji biblioteki semaphore

# Do czego służy

Program realizują problem wzajemnego wykluczenia procesów przy użyciu semaforów.

- sem_controler.x - program przygotowujący środowisko do realizacji problemu wyklczenia
- sem_user.x - proram używający smafora do realizacji problemu wykluczenia
- semaphore.o - biblioteka abstrachująca działanie i używanie semaforów

# Jak uruchomić program

```bash
make run # Uruchamia programy realizujące problem wykluczania
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