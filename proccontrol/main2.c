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
        fprintf(stderr, "Usage: %s [-s] [-e] <duration1> <duration2> ... <durationN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Parent process waiting for the pumps to complete...\n");

    int sequential = 0; // Flag to determine sequential execution
    int extraParallel = 0; // Flag to determine if an extra process should run in parallel

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-s") == 0)
        {
            sequential = 1;
        }
        else if (strcmp(argv[i], "-e") == 0)
        {
            extraParallel = 1;
        }
    }

    // Adjusting argc and argv based on flags
    int adjustedArgc = argc;
    char **adjustedArgv = argv;

    if (sequential)
    {
        adjustedArgc--;
        adjustedArgv++;
    }

    if (extraParallel)
    {
        adjustedArgc--;
        adjustedArgv++;
    }

    int numPumps = adjustedArgc - 1;
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
            int duration = atoi(adjustedArgv[i + 1]); // Convert duration from string to int
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

    if (extraParallel)
    {
        // Run an extra process in parallel
        pid_t extraPid = fork();

        if (extraPid == -1)
        {
            perror("Fork for extra process failed");
            exit(EXIT_FAILURE);
        }

        if (extraPid == 0)
        {
            // Child process for the extra parallel task
            printf("Extra parallel process started.\n");
            // Perform the extra task here
            printf("Extra parallel process completed.\n");
            exit(EXIT_SUCCESS);
        }

        // Parent process waiting for the extra parallel process to complete
        waitpid(extraPid, NULL, 0);
    }

    free(pids);

    return 0;
}
