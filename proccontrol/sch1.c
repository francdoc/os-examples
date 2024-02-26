#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Keep this: gcc main.c -o main

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <duration1> <duration2> ... <durationN>\n", argv[0]);
        exit(EXIT_FAILURE);
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
    printf("Parent process waiting for the pumps to complete...\n");
    int *statuses = (int *)malloc(numPumps * sizeof(int));

    if (statuses == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numPumps; i++)
    {
        waitpid(pids[i], &statuses[i], 0);
    }

    for (int i = 0; i < numPumps; i++)
    {
        if (WIFEXITED(statuses[i]))
        {
            printf("Pump %d exited with status %d.\n", i + 1, WEXITSTATUS(statuses[i]));
        }
        else
        {
            printf("Pump %d did not exit successfully.\n", i + 1);
        }
    }

    free(pids);
    free(statuses);

    return 0;
}
