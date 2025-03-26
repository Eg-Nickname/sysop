## Autor: Jakub Kurek

### Data: 25-03-2025

# Co zawiera

Folder zawiera pliki:
- README - informacje o programach i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:
- cw3a.c
- cw3b.c 
- cw3c_master.c 
- cw3c_spawner.c

# Do czego służy
- cw3a.x - program przyjmujący sygnał, któremu ustawia wybraną metodę obsługi
- cw3b.x - program, tworzący proces potomny a nastepnie wysyłający do niego sygnał
- cw3c_master.x - program tworzy program potomny i przesyła do niego resztę parametrów
- cw3c_spawner.x - tworzy nowe procesy potomne na podstawie przekazanych parametrów. 
                   ustawia siebie jako lidera grupy i przesyła do całej grupy wybrany sygnał 

# Jak uruchomić program

Program można uruchomić przy użyciu polecenia
```bash
make runa SIG=numer_sygnalu SIG_HANDLING=typ_obslugi # Uruchamia program z cw3a wraz z parametrami domyślnymi
make runb SIG=numer_sygnalu SIG_HANDLING=typ_obslugi # Uruchamia program z cw3b wraz z parametrami domyślnymi
make runc SIG=numer_sygnalu SIG_HANDLING=typ_obslugi SPAWNER_PROG=program_tworzacy_procesy # Uruchamia program z cw3c wraz z parametrami domyślnymi
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