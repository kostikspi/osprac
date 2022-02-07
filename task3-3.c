#include <stdio.h>

int main(int argc, char* argv[], char* envp[]) {
    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }

    printf("\n");

    while(1) {
        if (*envp == NULL) {
            break;
        }
        printf("%s\n", *envp);
        envp += 1;
    }
    return 0;
}

