#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    int x = 100;
    
    pid = fork();
    if (pid == 0) {
        printf("child : x=%d\n", ++x);
        exit(0);
    }

    printf("parent: x=%d\n", --x);
    exit(0);
}