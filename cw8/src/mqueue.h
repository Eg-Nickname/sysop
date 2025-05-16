#ifndef MQUEUE_LIB
#define MQUEUE_LIB

#include <stddef.h>

// Ułatwienie nazwy typu atrybutów kolejki
typedef struct mq_attr queue_attr;

// Funkcja tworzy koleję i zwraza 0 w przypadku porazki lub jej deskryptor w
// przypadku sukcesu.
int queue_create(const char* name, long queue_max_msg, long queue_msg_size);

// Funkcja otwiera koleję i zwraza 0 w przypadku porazki lub jej deskryptor w
// przypadku sukcesu.
int queue_open(const char* name, int oflag);

// Funkcja zamyka kolejkę o podanym deskryptorze. Zwraca 0 w przypadku porażki
// lub 1 w przypadku sukcesu.
int queue_close(int qd);

// Funkcja usuwająca koleję komunikatów. Zwraca 0 w przypadku błędu lub 1 w
// przypadku sukcesu.
int queue_destroy(const char* name);

// Funkcja pobierająca atrybuty kolejki. Zwraca 0 w przypadku błędu lub 1 w
// przyadku sukcesu wraz z atrybutami w miejscu podanym przez wskaźnik.
int queue_get_attr(int qd, queue_attr* attr_ptr);

// Funkcja wysyła wiadomośc do kolejki. Zwraca 0 w przypadku błędu lub 1 w
// przypadku suckecu.
int queue_send(int qd, char* msg_ptr, size_t msg_size, unsigned int priotrity);

// Funkcja odbiera wiadomośc z kolejki. Zwraca 0 w przypadku błędu lub 1 w
// przypadku suckecu
int queue_recive(int qd, char* msg_ptr, size_t msg_size);

#endif
