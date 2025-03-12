#define _XOPEN_SOURCE
#define  _XOPEN_SOURCE_EXTENDED

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void print_process_info()
{
    int uid = getuid();
    int gid = getgid();
    int pid = getpid();
    int ppid = getppid();
    int pgid = getpgid(0);
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d \n", uid, gid, pid, ppid, pgid);
}