// ======================================================================================
// Plik z deklaracją funkjci zawarych w biliotece pamięci dzielonej
// ======================================================================================
// Jakub Kurek 07-05-2025
// ======================================================================================
#ifndef SHERD_MEM_LIB
#define SHERD_MEM_LIB

#include <sys/types.h>
// Funkcja tworzy pamięć dzieloną. Zwraca 0 w przypadku błędu lub deskryptor
// pamięci w razie powodzenia.
int create_shm(const char* name);
// Funkcja ustala rozmiar dla stworzonej pamięci dzielonej
int init_shm(int shm_fd, off_t size);
// Funkcja zwraca 0 w przypadku braku pamięci dzielonej lub jej deskryptor w
// razie powodzenia.
int open_shm(const char* name);
// Funkcja zamyka pamięć dzieloną dla podanego deskryptora. Zwraca 0 w przypadku
// błędu lub 1 w przypadku sukcesu.
int close_shm(int shm_fd);
// Funkcja usuwa obiekt pamięci dzieonej. Zwraza 0 w przypadku błedu lub 1 w
// przypadku sukcesu.
int destroy_shm(const char* name);

#endif
