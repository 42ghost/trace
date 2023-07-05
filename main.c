#include "trace.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("ERROR: not enough args");
        return 1;
    }
    
    pid_t child_pid = fork();
    
    if (child_pid == 0)
    {
    	// traced process
        t_process(argc - 1, argv + 1);
    } else {
    	// tracer
        trace(child_pid);
    }
    
    return 0;
}
