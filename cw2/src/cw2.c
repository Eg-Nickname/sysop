#define _XOPEN_SOURCE
#define  _XOPEN_SOURCE_EXTENDED
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void print_process_info();

int main(int argc, char **argv)
{
    if(argc != 2){
        fprintf(stderr, "Nie podano ścieżki programu do wykonania. Poprawne użycie \n");
        fprintf(stderr, "%s ./sciezka_do_pliku.x \n", argv[0]);
        exit(1);
    }

    printf("Proces macierzysty - ");
    print_process_info();

    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            // Fork error code
            perror("fork error");
            exit(1);
        case 0:
            // Child process code
            execlp(argv[1], argv[1], NULL);
            perror("Execlp error");
            _exit(2);
            break;
        default:
            // Parent process code
            if(wait(NULL)==-1){
                perror("Wait error");
                exit(3);
            }
            break;
        };
    }
    return 0;
}

void print_process_info()
{
    int uid = getuid();
    int gid = getgid();
    int pid = getpid();
    int ppid = getppid();
    int pgid = getpgid(0);
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d \n", uid, gid, pid, ppid, pgid);
}