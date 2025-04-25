#include <semaphore.h>

sem_t* create_sem(int init_val);
sem_t* create_named_sem(const char* name, int init_val);
sem_t* open_named_sem(const char* name);
int destroy_sem(sem_t*);
int destroy_named_sem(const char* name);

int get_sem_val(sem_t*, int*);
int sem_p(sem_t* sem);
int sem_w(sem_t* sem);
