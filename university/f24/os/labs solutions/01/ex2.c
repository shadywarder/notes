#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    printf("PID = [%d]", pid);
    
    sleep(3);

    kill(pid, SIGKILL);
}