#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

const char *pathname = "task7-1w.c";

int main() {
    int sh_mem_fd = 0;
    int size = 1003;

    key_t sh_mem_key;
    if ((sh_mem_key = ftok(pathname, 0)) < 0) {
        printf("Error: %s", strerror(errno));
        exit(-1);
    }

    if ((sh_mem_fd = shmget(sh_mem_key, size, 0)) < 0) {
        printf("Error: %s", strerror(errno));
        exit(-1);
    }

    char *sh_mem;
    if ((sh_mem = shmat(sh_mem_fd, NULL, 0)) == (char *) (-1)) {
        printf("Error: %s", strerror(errno));
        exit(-1);
    }
    printf("%s", sh_mem);
    if (shmctl(sh_mem_fd, IPC_RMID, NULL) < 0) {
        printf("Error: %s", strerror(errno));
        exit(-1);
    }

    //Net voine
    return 0;
}