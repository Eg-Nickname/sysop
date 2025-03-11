#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
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
            sleep(1);
            printf("    Proces potomny - ");
            print_process_info();
            break;
        default:
            // Parent process code
            // Do nothing
            break;
        };
    }
    return 0;
}