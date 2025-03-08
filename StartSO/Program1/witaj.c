/* 
 Program wypisuje powitanie w losowo wybranych miejscach na ekranie.
 ----------------------------------------------------------------------
 Autor: Wieslaw Placzek,                             Krakow, 21.02.2025
 ----------------------------------------------------------------------
*/ 

// Wybor wlasciwej definicji funkcji getline dla aktualnej wersji
// biblioteki glibc; patrz: man getline
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

#define XMAX 60      // Maksymalna liczba kolumn ekranu 
#define YMAX 20      // Maksymalna liczba wierszy ekranu
#define NMAX 10      // Liczba wypisan na ekran

/*
  =========================================================================
  Ustawienie pozycji kursora w punkcie o wspolrzednych (x,y) na ekranie,
  gdzie x - liczba kolumn (od lewej), y - liczba wierszy (od gory).
  Sekwencja \033[2K powoduje wymazanie poprzedniego napisu w danym wierszu.
  =========================================================================
*/
void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH\033[2K", y, x);
}

// Przyklad funkcji do rejestracji przez atexit() w celu wywolania jej
// przez funkcje exit() lub instrukcje return funkcji main().
void koniec(void)
{
  printf("\n>>> Koniec procesu - porzadki wykonane!\n\n");
}

int main(void)
{
  // Rejestracja funkcji koniec() do wywolania przez exit()
  if (atexit(koniec) != 0) {
    perror("Error in call to atexit() function");
    exit(EXIT_FAILURE);
  }
  
  printf("\033[5;7m");     // Wlacz migotanie i odwrotny obraz
  printf("--- Wpisz swoje imie:");
  printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania
  printf(" ");
  // Wczytaj imie (dla ponizszych ustawien getline dynamicznie przydziela odpowiednia tablice)
  char *imie = NULL;  
  size_t rtab = 0;
  ssize_t dlim;
  if ( (dlim = getline(&imie,&rtab,stdin) ) == -1) {
    perror("Error in call to getline() function");
    exit(EXIT_FAILURE);
  }
  // Stworz tekst powitania
  char witaj[] = "Witaj";
  int dlpo = sizeof(witaj) + dlim + 1; // minimalny rozmiar tablicy na tekst (+ 1 dla znaku '\0')
  char *powitanie = malloc(dlpo);     // dynamiczny przydzial pamieci na tekst powitania
  assert(powitanie);                  // asercja - zglasza blad gdy: powitanie == NULL
  // Tekst powitania wpisz do tablicy powitanie laczac dwie tablice znakowe: witaj i imie
  if (snprintf(powitanie,dlpo,"%s %s",witaj,imie) < 0) {
    perror("Error in call to snprintf() function");
    exit(EXIT_FAILURE);
  }
  powitanie[dlpo - 2] = '!'; // wstaw znak '!' (zamiast '\n') przed koncowym znakiem '\0'
  // Wyczysc ekran wywolujac polecenie clear powloki przy pomocy funkcji system
  if (system("clear") == -1) {
    perror("Error in call to system() function");
    exit(EXIT_FAILURE);
  }
  srand(time(NULL)%1000);  // Zainicjuj generator liczb losowych przy uzyciu czasu systemowego 
  printf("\033[1;4m");     // Wlacz pogrubienie i podkreslenie

  // Powtarzaj wypisywanie NMAX razy
  for (int i = 0; i < NMAX; i++) {
    // Wybieraj losowo wspolrzedne kursora (x,y)
    int x = 1 + (int) ( 1.0*XMAX*rand()/(RAND_MAX + 1.0) );
    int y = 1 + (int) ( 1.0*YMAX*rand()/(RAND_MAX + 1.0) );
    gotoxy(x, y);
    printf("%s\n",powitanie);
    sleep(1);              // Poczekaj chwile
  } // for
  free(powitanie); powitanie = NULL; // Zwolnij pamiec na stercie i wyzeruj wskaznik
  printf("\033[0m");                 // Wroc do domyslnego trybu wyswietlania
  gotoxy(0, YMAX+1);
}

