#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Keep this: gcc main.c -o main

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s [-s] <duration1> <duration2> ... <durationN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Parent process waiting for the pumps to complete...\n");

    int sequential = 0; // Flag to determine sequential execution
    if (argc > 2 && strcmp(argv[1], "-s") == 0)
    {
        sequential = 1;
        argc--;
        argv++;
    }

    int numPumps = argc - 1;
    pid_t *pids = (pid_t *)malloc(numPumps * sizeof(pid_t));

    if (pids == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numPumps; i++)
    {
        if (sequential && i > 0)
        {
            // If sequential flag is set, wait for the previous process to complete before forking the next one
            waitpid(pids[i - 1], NULL, 0);
        }

        pids[i] = fork();

        if (pids[i] == -1)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0)
        {
            // Child process
            int duration = atoi(argv[i + 1]); // Convert duration from string to int
            printf("Pump %d started. Waiting for %d seconds...\n", i + 1, duration);
            sleep(duration);
            printf("Pump %d completed.\n", i + 1);
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process
    for (int i = 0; i < numPumps; i++)
    {
        waitpid(pids[i], NULL, 0);
    }

    free(pids);

    return 0;
}
