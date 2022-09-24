#include "kernel/types.h"
#include "user/user.h"

void filter(int* pread){
    close(pread[1]);
    int pwrite[2], n, buf;
    pipe(pwrite);
    if (read(pread[0], &n, sizeof(int))){
        printf("prime %d\n", n);
        if (fork() == 0){
            filter(pwrite);
            exit(0);
        }
        else{
            close(pwrite[0]);
            while (read(pread[0], &buf, sizeof(int))){
                if (buf % n != 0){
                    write(pwrite[1], &buf, sizeof(int));
                }
            }
            close(pread[0]);
            close(pwrite[1]);
            wait(0);
        }
    }
}

int main(int argc, char** argv){
    if (argc > 1){
        fprintf(2, "usage: primes\n");
        exit(1);
    }

    int p[2], i;
    pipe(p);

    if (fork() == 0){
        filter(p);
        exit(0);
    }
    else {
        close(p[0]);
        for (i = 2; i <= 35; i++){
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    }

    exit(0);
}