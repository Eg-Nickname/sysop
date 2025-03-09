#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "process_info.h"

int main(int argc, char **argv)
{
    printf("Proces macierzysty - ");
    print_process_info();
    // Generation of child process
    int gen = 0;
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
            // Wait for prev generations to print their info
            sleep(gen);
            gen++;
            printf("    Proces potomny gen %d - ", gen);
            print_process_info();
            break;
        default:
            // Parent process code
            // Do nothing
            break;
        };
    }
    // Wait for all child processes to end
    for (int i = gen; i <= 3; i++)
    {
        sleep(i);
    }

    return 0;
}