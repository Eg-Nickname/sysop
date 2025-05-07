// ======================================================================================
// Plik z deklaracją funkjci zawarych w biliotece z semaforami
// ======================================================================================
// Jakub Kurek 29-04-2025
// ======================================================================================
#ifndef SEM_LIB
#define SEM_LIB

#include <semaphore.h>
// Funkcja tworyz zwykły semafor. Zwraca null_ptr w przypadku błędu lub ptr w
// przypadku sukcesu.
sem_t* create_sem(int init_val);
// Funkcja tworzy nazwany semafor. Zwraca null_ptr w przypadku błędu lub ptr w
// przypadku sukcesu.
sem_t* create_named_sem(const char* name, int init_val);
// Funkcja otwiera nazwany semafor. Zwraca null_ptr w przypadku błędu lub ptr w
// przypadku sukcesu.
sem_t* open_named_sem(const char* name);
// Funkcja usuwa  zwykły semafor. Zwraca 0 w przypadku błędu lub 1 w przypadku
// sukcesu.
int destroy_sem(sem_t*);
// Funkcja usuwa nazwany semafor. Zwraca 0 w przypadku błędu lub 1 w przypadku
// sukcesu.
int destroy_named_sem(const char* name);
// Funkcja zwraca wartość semafora w lokalizacji podanej jako parametr. Zwraca 0
// w przypadku błędu lub 1 w przypadku sukcesu.
int get_sem_val(sem_t*, int*);
// Funkcja podnosi semafor. Zwraca 0 w przypadku błędu lub 1 w przypadku
// sukcesu.
int sem_p(sem_t* sem);
// Funkcja opuszcza semafor. Zwraca 0 w przypadku błędu lub 1 w przypadku
// sukcesu.
int sem_w(sem_t* sem);

#endif
