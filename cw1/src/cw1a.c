// ======================================================================================
// Program wypisujący informacje o procesie w którym jest on wykonywany
// ======================================================================================
// Jakub Kurek 09-03-2025
// ======================================================================================

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "process_info.h"

int main(int argc, char **argv)
{
    print_process_info();
    return 0;
}