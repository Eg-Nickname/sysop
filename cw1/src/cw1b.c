#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "process_info.h"

int main(int argc, char **argv)
{
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
            printf("    Proces potomny - ");
            print_process_info();
            break;
        default:
            // Parent process code
            wait(NULL);
            break;
        };
    }
    return 0;
}