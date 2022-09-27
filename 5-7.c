#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    pid_t pid;
    
    pid = fork();
    
    if (pid == 0)
    {
        close(STDOUT_FILENO);
        printf("Hello World from child process\n");
        exit(0);
    }

    wait(NULL);
    printf("Child process terminated\n");
    exit(0);
}