## Problem producenta konsumenta dla wielu producentów i konsumentów
```
    // Pseudokod dla problemu Producenta i Konsumenta z buforem cyklicznym.
    // Wspolny bufor do przesylania danych znajduje sie w pamieci dzielonej.
    // Dostep do bufora jest synchronizowany semaforami.

    #define N ? // Rozmiar bufora
    
    typdef struct { ... } Towar; // Definicja typu dla jednostek towaru
    Towar bufor[N]; // Bufor mogacy pomiescic N jednostek towaru
    int wstaw = 0, wyjmij = 0; // Pozycje wstawiania oraz wyjmowania towaru
    
    // z bufora (mozna umiescic w pamieci dzielonej)
    semaphore BUF_TO_WRITE = N; // Semafor do wstrzymywania Producentów w buforze
    semaphore BUF_TO_READ = 0; // Semafor do wstrzymywania Konsumentów na buforze
    semaphore BUF_BLOCK_WRITE = 1; // Blokowanie dostępu odczytu 
    semaphore BUF_BLOCK_READ  = 1; // Blokowanie zapisu do bufora


    // Procesy Producenta
    // ----------------
    Towar towarProd;
    while (1) {
        // Produkcja towaru
        P(BUF_BLOCK_WRITE); // Blokujemy dostep dla producentów na czas zapisu do bufora
        P(BUF_TO_WRITE); // Opusc semafor Producenta (zmniejszenie ilości danych możliwych do zapisu w buforze)
        bufor[wstaw] = towarProd; // Umiesc towar w buforze
        wstaw = (wstaw + 1) % N; // Przesun pozycje wstawiania o 1 dalej
        V(BUF_BLOCK_WRITE); // Odblokowujemy dostęp do bufora dla producentów
        V(BUF_TO_READ); // Podniesc semafor Konsumenta (zwiększenie ilośći danych do oczytu)
    }

    // Procesy Konsumenta
    // ----------------
    Towar towarKons;
    while (1) {
        P(BUF_BLOCK_READ); // Blokujemy dostęp dla konsumentów do odczytu
        P(BUF_TO_READ); // Opusc semafor Konsumenta (czekanie na nowe dane)
        towarKons = bufor[wyjmij]; // Wyciągnij dane z bufora
        wyjmij = (wyjmij + 1) % N; // Przesun pozycje wyciągania o 1 dalej
        V(BUF_BLOCK_READ); // Odblokowjemy dostęp dla konsumentów do oczytu
        V(BUF_TO_WRITE); // Podniesc semafor Producenta (zwiększenie ilości danych do zapisu)
        // Konsumpcja towaru
    }
```