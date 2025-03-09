#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "process_info.h"

int main(int argc, char **argv)
{
    print_process_info();
    return 0;
}