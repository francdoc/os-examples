/* 
 * This is a very minimal shell.  It is only required to find an executable
 * in the PATH, then load it and execute it (using execv).  Since it uses
 * "." (dot) as a separator, it cannot handle file names like "minishell.h"
 * The focus on this exercise is to use fork, PATH variables, and exec.
 * This code can be extended by doing the exercise at the end of Chapter 9.
 *
 * Provided as a solution to Kernel Projects by Gary Nutt with contributions
 * by Sam Siewert and Panos Tsirigotis
 *
 * Modified by Sam Siewert (2013) to remove gets() call considerd dangerous and
 * replaced with recommended fgets with line-feed stripping.
 *
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<string.h>
#include	<unistd.h>
#include	"minishell.h"


char *lookupPath(char **, char **);
int parseCommand(char *, struct command_t *);
int parsePath(char **);
void printPrompt();
void readCommand(char *);

char promptString[] = "in a nutt shell >";
extern FILE *stdin;

int main() 
{
    char commandLine[LINE_LEN];
    char *pathv[MAX_PATHS];
    int numPaths;
    int i, j, len;
    int chPID;		// Child PID
    int stat;		// Used by parent wait
    pid_t thisChPID;
    struct command_t command;

    // Shell initialization
    for(i=0; i<MAX_ARGS; i++)
        command.argv[i] = (char *) malloc(MAX_ARG_LEN);

    parsePath(pathv);

    // Main loop
    while(TRUE) 
    {
        printPrompt();

        // Read the command line and parse it
        readCommand(commandLine);
        printf("commandLine=%s\n", commandLine);

        if( (strcmp(commandLine, "exit") == 0) ||
            (strcmp(commandLine, "quit") == 0))
        {
            break;	// Quit the shell
        }

        parseCommand(commandLine, &command);

#ifdef DEBUG
        printf("... returned from parseCommmand ...\n");

        for(i=0; i<command.argc; i++)
            printf("	argv[%d] = %s\n", i,  command.argv[i]);
#endif

        // Get the full pathname for the file
        command.name  = lookupPath(command.argv, pathv);

#ifdef DEBUG
        printf("... returned from lookupPath ...\n");
        printf("	command path = %s\n", command.name);
        for(i=0; i<command.argc; i++)
	    printf("	argv[%d] = %s\n", i,  command.argv[i]);
#endif

        if(command.name == NULL) 
        {
            fprintf(stderr, "Command %s not found\n", command.argv[0]);
            continue;
        }

        // Create a process to execute the command
        if((chPID = fork()) == 0) 
        {
            //  This is the child, that will execute the command requested

#ifdef DEBUG
            printf("child executing: %s\n", command.name);
            for(i=1; i<command.argc; i++)
	            printf("	argv[%d] = %s\n", i,  command.argv[i]);
#endif

            execv(command.name, command.argv);
       }

       // Wait for the child to terminate

#ifdef DEBUG
       printf("Parent waiting\n");
#endif

        thisChPID = wait(&stat);
  }

// Shell termination

}


char *lookupPath(char **argv, char **dir) 
{

    // This function inspired by one written by Sam Siewert in Spring 1996
    int i;
    char *result;
    char pName[MAX_PATH_LEN];

    // Check to see if file name is already an absolute path name
    if(*argv[0] == '/') 
    {
        result = (char *) malloc(strlen(argv[0])+1);
        strcpy(result, argv[0]);
        return result;
    }

    // Look in PATH directories
    // This code does not handle the case of a relative pathname
    for(i = 0; i < MAX_PATHS; i++) 
    {
        if(dir[i] == NULL) break;
        strcpy(pName, dir[i]);
        strcat(pName, "/");
        strcat(pName, argv[0]);

#ifdef DEBUG
        printf("lookupPath: Checking for %s\n", pName);
#endif

        if(access(pName, X_OK | F_OK) != -1) 
        {

            // File found
#ifdef DEBUG
            printf("lookupPath: Found %s in %s (full path is %s)\n",
			argv[0], dir[i], pName);
#endif
            result = (char *) malloc(strlen(pName)+1);
            strcpy(result, pName);
            return result;		// Return with success
        }
    }

    // File name not found in any path variable
    fprintf(stderr, "%s: command not found\n", argv[0]);
    return NULL;

}


int parseCommand(char *cLine, struct command_t *cmd) 
{
    // Determine command name and construct the parameter list
    int argc;
    int i, j;
    char **clPtr;

    // Initialization
    clPtr = &cLine;
    argc = 0;

    // Get the command name and parameters
    // This code does not handle multiple WHITESPACE characters
    while((cmd->argv[argc++] = strsep(clPtr, WHITESPACE)) != NULL) ;

    cmd->argv[argc--] = '\0';	// Null terminated list of strings
    cmd->argc = argc;

    return  1;	
}


int parsePath(char *dirs[]) 
{
    // This routine based on one written by Panos Tsirigotis, Spring 1989
    int i;
    char *pathEnvVar;
    register char *thePath, *oldp;

    for(i=0; i<MAX_ARGS; i++)
	dirs[i] = NULL;

    pathEnvVar = (char *) getenv("PATH");
    thePath = (char *) malloc(strlen(pathEnvVar) + 1);
    strcpy(thePath, pathEnvVar);

    i = 0;
    oldp = thePath;

    for(;; thePath++) 
    {
	if((*thePath == ':') || (*thePath == '\0')) 
        {
            dirs[i] = oldp;
            i++;

            if(*thePath == '\0') break;

            *thePath = '\0';
            oldp = thePath + 1;
        }
    }

#ifdef DEBUG
    printf("Directories in PATH variable\n");
        for(i=0; i<MAX_PATHS; i++)
            if(dirs[i] != '\0')
		printf("	Directory[%d]: %s\n", i, dirs[i]);
#endif

}


void printPrompt() 
{
    printf("%s ", promptString);
}

void readCommand(char *buffer) 
{
    // original dangerous stdio call - can over-run buffer, see man gets
    // gets(buffer); 

  
    // suggested safer replacement call - can't go beyond length provided,
    // but we must strip off the line feed included in the buffer unlike gets
    // 
    fgets(buffer, LINE_LEN, stdin);

    buffer[strlen(buffer)-1] = '\0';  // overwrite the line feed with null term

    printf("readCommand buffer=%s\n", buffer);
}
