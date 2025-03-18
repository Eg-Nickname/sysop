// ======================================================================================
// Program wypisuje informacje o procesie, w którym jest wykonywany
// ======================================================================================
// Jakub Kurek 18-03-2025
// ======================================================================================

#define _XOPEN_SOURCE
#define  _XOPEN_SOURCE_EXTENDED

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int uid = getuid();
    int gid = getgid();
    int pid = getpid();
    int ppid = getppid();
    int pgid = getpgid(0);
    printf("Informacja z procesu wywołanego przez execlp - ");
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d \n", uid, gid, pid, ppid, pgid);

    return 0;
}