#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "semaphore.h"

sem_t* create_sem(int init_val) {
    sem_t* sem_ptr = malloc(sizeof(sem_t));
    if (sem_init(sem_ptr, 1, init_val) == -1) {
        perror("sem_init error");
        free(sem_ptr);
        return NULL;
    } else {
        return sem_ptr;
    }
}

sem_t* create_named_sem(const char* name, int init_val) {
    sem_t* sem_ptr = sem_open(name, O_CREAT | O_EXCL, 0600, init_val);
    if (sem_ptr == SEM_FAILED) {
        perror("named sem create error");
        return NULL;
    } else {
        return sem_ptr;
    }
}

sem_t* open_named_sem(const char* name) {
    sem_t* sem_ptr = sem_open(name, O_CREAT);
    if (sem_ptr == SEM_FAILED) {
        perror("named sem opens  error");
        return NULL;
    } else {
        return sem_ptr;
    }
}

int destroy_sem(sem_t* sem_ptr) {
    int sem_dest_ret = sem_destroy(sem_ptr) + 1;
    if (!sem_dest_ret) {
        perror("sem_destroy error");
    }
    free(sem_ptr);
    return sem_dest_ret;
}

int destroy_named_sem(const char* name) {
    int sem_unlink_ret = sem_unlink(name) + 1;
    if (!sem_unlink_ret) {
        perror("sem_unlink error");
    }
    return sem_unlink_ret;
}

int get_sem_val(sem_t* sem_ptr, int* sem_val_ptr) {
    int sem_getval_ret = sem_getvalue(sem_ptr, sem_val_ptr) + 1;
    if (!sem_getval_ret) {
        perror("sem_getval error");
    }
    return sem_getval_ret;
}

int sem_p(sem_t* sem) {
    int sem_post_ret = sem_post(sem) + 1;
    if (!sem_post_ret) {
        perror("sem_post error");
    }
    return sem_post_ret;
}
int sem_w(sem_t* sem) {
    int sem_wait_ret = sem_wait(sem) + 1;
    if (!sem_wait_ret) {
        perror("sem_wait error");
    }
    return sem_wait_ret;
}
