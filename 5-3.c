#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sig_handler(int signum) {
    printf("goodbye\n");
    exit(0);
}

int main (int argc, char *argv[]) {
    pid_t pid, parent_pid = getpid();
    
    sigset_t mask, prev_mask;
    
    sigemptyset(&mask);
    sigaddset(&mask, SIGCONT);
    sigprocmask(SIG_BLOCK, &mask, &prev_mask); //Block SIGCONT and save previous blocked set
    
    pid = fork();
    
    if (pid == 0)
    {
        printf("hello\n");
        kill(parent_pid, SIGCONT); //Send signal to parent process
        exit(0);
    }

    signal(SIGCONT, sig_handler); //Install signal handler
    sigsuspend(&prev_mask); //Wait until signal received
    sigprocmask(SIG_SETMASK, &prev_mask, NULL); //Restore previous blocked set, unblocking SIGCONT
    pause();
    exit(0);
}