// ======================================================================================
// Biblioteka służąca do łatwiejszego korzystania z mechanizmu pamięci dzielonej
// ======================================================================================
// Jakub Kurek 07-05-2025
// ======================================================================================

#define _XOPEN_SOURCE 1001
#define _XOPEN_SOURCE_EXTENDED

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "shared_mem.h"

int create_shm(const char* name) {
    int shm_ret = shm_open(name, O_CREAT | O_EXCL | O_RDWR, 0666);
    if (shm_ret == -1) {
        perror("shm create error");
        return 0;
    }
    return shm_ret;
}

int init_shm(int shm_fd, off_t size) {
    if (ftruncate(shm_fd, size) + 1) {
        return 1;
    } else {
        perror("ftruncate error");
        return 0;
    }
}

int open_shm(const char* name) {
    int shm_ret = shm_open(name, O_RDWR, 0666);
    if (shm_ret == -1) {
        perror("shm open error");
        return 0;
    }
    return shm_ret;
}

int close_shm(int shm_fd) {
    if (close(shm_fd) + 1) {
        return 1;
    } else {
        perror("shm close error");
        return 0;
    }
}

int destroy_shm(const char* name) {
    if (shm_unlink(name) + 1) {
        return 1;
    } else {
        perror("shm unlink error");
        return 0;
    }
}
