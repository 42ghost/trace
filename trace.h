#include <sys/ptrace.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <signal.h>

int t_process(int argc, char** argv);
int trace(pid_t child);

