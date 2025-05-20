## Autor: Jakub Kurek

### Data: 20-05-2025

# Do czego służy
Programy symulujące rozwiązanie klient serwer, w którym klienci przesyłają do serwera dane do obliczenia przy użyciu kolejek komunikatów. Klienci wczytują dane z klawiatury od uzytkownika i wysyłają je do serwera. Serwer odczytuje wiadomości i przesyła rozwiązania poprzez kolejki komunikatów utowrzone przez klientów.

# Co zawiera

Folder zawiera pliki:
- README - informacje o programach i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:
- check_error.h - makra sprawdzajace poprawność wykonanych funkcji bibliotecznych
- mqueue.h - deklaracje funckji pomocniczych kolejek komunikatów
- mqueue.c - definicje funckji pomocniczych kolejek komunikatów
- client.c - program symulujący klienta
- server.c - program symulujący serwer

# Jak uruchomić program
```bash
make runs # Uruchamia proces serwera
make runc # Uruchamia proces klienta
make runall # Uruchamia proces serwera oraz 2 procesy klientów
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