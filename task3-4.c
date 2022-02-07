
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[], char* envp[]) {
    pid_t pid = fork();

    if (pid == -1) {
        printf("Error!\n");
    } else if (pid == 0) {
        printf("In child\n");
        execle("/bin/whoami", "/bin/whoami", NULL, envp);
    } else {
        printf("In parent\n");
    }
}