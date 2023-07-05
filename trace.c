#include "trace.h"

#include <stdio.h>

int t_process(int argc, char** argv)
{
    int ret = execv(argv[0], argv);
    return ret;
}

int trace(pid_t child)
{
    // Attaches to the process
    ptrace(PTRACE_ATTACH, child, 0, 0);
    ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);

    int status, num_of_sc, ret;
    while(1)
    {
        ptrace(PTRACE_SYSCALL, child, 0, 0);
        waitpid(child, &status, 0);
        
        if (WIFEXITED(status))
            break;
        
        // gets system call number
        num_of_sc = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX);
        printf("%d\t", num_of_sc);
        
        ptrace(PTRACE_SYSCALL, child, 0, 0);
        waitpid(child, &status, 0);
        
        // gets the return value of the system call
        ret = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RAX);
        printf("=\t%d\n", ret);
    }
    
    // Dettaches from the process
    ptrace(PTRACE_DETACH, child, 0, 0);
    return 0;
}

