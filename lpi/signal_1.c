#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void sigint_handler(int signo) {
    if (signo == SIGINT) {
        printf("Received SIGINT (Ctrl+C). Exiting...\n");
        exit(0);
    }
}

int main() {
    // Register the signal handler
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Error setting up signal handler");
        return 1;
    }

    printf("Press Ctrl+C to trigger SIGINT...\n");

    // Infinite loop to keep the program running
    while (1) {
        // Do some work or just sleep
        sleep(1);
    }

    return 0;
}

// gcc signal_1.c -o signal_1