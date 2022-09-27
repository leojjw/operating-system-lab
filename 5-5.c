#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    pid_t pid;
    
    pid = fork();
    
    if (pid == 0)
    {
        int wc = wait(NULL);
        printf("Child process: wait() returned with %d\n", wc);
        exit(0);
    }
    
    printf("Child process ID: %d\n", pid);
    int rc_wait = wait(NULL);
    printf("Parent process: wait() returned with %d\n", rc_wait);

    exit(0);
}