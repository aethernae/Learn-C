#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        /* code here */
        printf("ren_shell> ");
        fflush(stdout);
        
        if(fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if(strcmp(line, "exit") == 0) {
            break;
        }

        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        if (args[0] == NULL) continue;

        pid_t pid = fork();

        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                printf("Perintah '%s' tidak ditemukan!\n", args[0]);
            }
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            printf("Gagal melakukan fork! \n");
        }
    }
    return 0;
}