## Autor: Jakub Kurek

### Data: 20-05-2025

# Do czego służy
Program służy pokazania rozwiązania problemu wzajemnego wykluczania wątków przy uzyciu algorytmu piekarni. Program tworzy liczbę wątków, podaną jako argument. Kazdy wątek w swojej sekcji krytycznej wykonuje odczyt globalnego licznika, zwiększenie go lokoalnie, zasymulowanie innych operacji podczas uśpienie go na pareset ms oraz zapisanie zwiększonej wartości do zmiennej globalnej. Na końcu program porównuje oczekiwaną wartość licznika globalnego z jego otrzymaną wartością.
 
# Co zawiera

Folder zawiera pliki:
- README - informacje o programach i użyciu
- Makefile - kompilacja, uruchamianie, archiwizacja programów
- src/ - katalog zawierający pliki źródłowe poszczególnych programów oraz biblioteki współdzielonej funkcji:

Katalog src:
- bakery_mutal_exclusion.c - główny program

# Jak uruchomić program
```bash
    make run #uruchomienie programu
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