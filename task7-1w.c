#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

const char *pathname = "task7-1w.c";

int main(int argc, char **argv) {
    FILE *file = fopen("task7-1w.c", "r");

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *program = malloc(size + 1);

    fread(program, size, 1, file);
    program[size] = 0;

    fclose(file);
    printf("Program size: %lu\n", size);

    key_t sh_mem_key;
    int sh_mem_fd;

    if ((sh_mem_key = ftok(pathname, 0)) < 0) {
        printf("Error: %s", strerror(errno));
        exit(-1);
    }

    if ((sh_mem_fd = shmget(sh_mem_key, size, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        printf("Error: %s", strerror(errno));
        exit(-1);
    }

    char *sh_mem;
    if ((sh_mem = shmat(sh_mem_fd, NULL, 0)) == (char *) (-1)) {
        printf("Error: %s", strerror(errno));
        exit(-1);
    }

    memcpy(sh_mem, program, size);
    return 0;
}