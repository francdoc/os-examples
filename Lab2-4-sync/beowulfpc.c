/* 
 * This is a very minimal example of two processes in a producer-consumer
 * relationship where one is a writer and the other is the reader.
 *
 * Provided as an example of sharing data between two processes using a
 * global file.
 *
 * In Linux all forms of inter-process communication are basically byte
 * streams.  These can be thought of as queues of characters.  The question
 * is, what if the producer over-writes the file (i.e. it is bounded rather 
 * than a continuos log of infinite length)?  In this example we therefore
 * limit the file to one line of text at a time and no more, so
 * messages sent from the producer to the consumer that exceed this length
 * must be broken up into multiple writes and the file closed and opened
 * each time.
 *
 * Note: The example as provided is expected to have synchronization
 *       problems and the goal for students is to explore the issues
 *       of data corruption using shared files and to explore possible
 *       solutions - in future labs we'll learn about "named pipes" that
 *       provide a solution as well (do "man mkfifo" to read about them).
 *       Likewise Linux pipes in general can be used (do "man pipe"), but
 *       before jumping to this solution provided by the OS, please try
 *       building your own solution (you are allowed to use semaphores
 *       and lockf, do "man lockf" to learn more).
 *
 * If we remove the bounds and just have a write logger and and a log reader
 * do we have any issues?
 *
 * The use of usleep to pace the parent and child so they alternate seems to help, but will this always work
 * if we increase RECITATIONS to a really large number?
 *
 * Try using usleep to sync with a large number of RECITATIONS and then do "diff child-log parent-log".
 *
 * Please play with the code and make modified versions to test solutions to
 * solve the problem of corruption.
 *
 * by Sam Siewert
 *
 */
#include	<stdio.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/stat.h>
#include	<semaphore.h>

#define TRUE (1)
#define FALSE (0)
#define VERSES (15)
#define LINE (52)
#define RECITATIONS (3)


// Beowulf - http://www.gutenberg.org/files/16328/16328-h/16328-h.htm
//
// The first 14 lines from the above translation.
//
char line[][LINE]={
                   "Lo! the Spear-Danes\' glory through splendid        \n",
                   "achievements                                       \n",
                   "The folk-kings\' former fame we have heard of,      \n",
                   "How princes displayed then their prowess-in-battle.\n",
                   "Oft Scyld the Scefing from scathers in numbers     \n",
                   "From many a people their mead-benches tore.        \n",
                   "Since first he found him friendless and wretched,  \n",
                   "The earl had had terror: comfort he got for it,    \n",
                   "Waxed \'neath the welkin, world-honor gained,       \n",
                   "Till all his neighbors o\'er sea were compelled to  \n",
                   "Bow to his bidding and bring him their tribute:    \n",
                   "An excellent atheling! After was borne him         \n",
                   "A son and heir, young in his dwelling,             \n",
                   "Whom God-Father sent to solace the people.         \n",
                   "                                                   \n",
                };


int main() 
{
    int i=0, j=0, bfd, logfd, nread, nwrite;
    int chPID;		// Child PID
    int stat;		// Used by parent wait
    int rc;		// return code
    pid_t thisChPID;
    sem_t *syncMsgWriterSem;
    sem_t *syncMsgReaderSem;
    char syncMsgWriterSemName[]="/BeowulfWriterSync";
    char syncMsgReaderSemName[]="/BeowulfReaderSync";

    // Create a process to produce Beowulf in a buffer bounded to the length of
    // a single line of verse and another to consume and record it.

    // set up syncrhonizing semaphore before fork
    //
    // shared with an initial value of zero for parent to increment
    //
    // open named semaphore
    syncMsgWriterSem=sem_open(syncMsgWriterSemName, O_CREAT, 0700, 0);
    syncMsgReaderSem=sem_open(syncMsgReaderSemName, O_CREAT, 0700, 0);


    if((chPID = fork()) == 0) //  This is the child, it is the Beowulf consumer
    {

        logfd=open("child-log", O_WRONLY | O_CREAT, 00600); 

        // READER Main loop
        while(j < RECITATIONS) 
        {
            // Wait for parent, the producer to indicate data ready
            printf("Child: taking syncMsg Writer semaphore\n");
            if(sem_wait(syncMsgWriterSem) < 0) perror("sem_wait syncMsgWriterSem Child");
            printf("Child: got synMsg Writer semaphore\n");


            // Open the bounded buffer file, and create if needed
            //
            // READ a LINE from the bounded buffer

            bfd=open("beowulfpipe", O_RDONLY | O_CREAT, 00600); 

            printf("Child: taking file lock\n");
            rc=lockf(bfd, F_LOCK, 0);

            nread=0;
            while(nread < LINE)
            {
                nread+=read(bfd, &line[i+nread], (LINE-nread));
                if(nread < LINE) printf("CHILD: partial line of %d\n", nread);
            }

            rc=lockf(bfd, F_ULOCK, 0); // not necessary, but added for clarity
            printf("Child: releasing file lock\n");

            close(bfd);


            // indicate to parent that message was read
            printf("Child: posting syncMsg Reader semaphore\n");
            if(sem_post(syncMsgReaderSem) < 0) perror("sem_post syncMsgReaderSem Child");
            printf("Child: posted syncMsg Reader semaphore\n");


            // Log what was READ
            nwrite=0;
            while(nwrite < LINE)
            {
                nwrite+=write(logfd, &line[i+nwrite], (LINE-nwrite));
            }

            // Have child nap 1 millisecond after each line
            //usleep(1000);

#ifdef DEBUG
            printf("CHILD:%s", line[i]);
#endif


            i++; i = i % VERSES; if(i==0) j++;
        }

        close(logfd);
 
        if(sem_close(syncMsgReaderSem) < 0) perror("sem_close syncMsgReaderSem Child");
        if(sem_close(syncMsgWriterSem) < 0) perror("sem_close syncMsgWriterSem Child");

        exit(0);

    }

    else // This is the parent that produces Beowulf for the child
    {

        logfd=open("parent-log", O_WRONLY | O_CREAT, 00600); 

        // WRITER Main loop
        while(j < RECITATIONS) 
        {

            // Open the bounded buffer file, and create if it does not already exist

            bfd=open("beowulfpipe", O_WRONLY | O_CREAT, 00600); 

            printf("Parent: taking file lock\n");
            rc=lockf(bfd, F_LOCK, 0);

            nwrite=0;
            while(nwrite < LINE)
            {
                nwrite+=write(bfd, &line[i+nwrite], (LINE-nwrite));
                if(nwrite < LINE) printf("PARENT: partial line of %d\n", nwrite);
            }

            rc=lockf(bfd, F_ULOCK, 0); // not necessary, but added for clarity
            printf("Parent: releasing file lock\n");

            close(bfd);


            // Post semaphore for Child to indicate data ready to consume
            printf("Parent: posting syncMsg Writer semaphore\n");
            if(sem_post(syncMsgWriterSem) < 0) perror("sem_post syncMsgWriterSem Parent");
            printf("Parent: posted syncMsg Writer semaphore\n");

            // Log what was WRITTEN
            nwrite=0;
            while(nwrite < LINE)
            {
                nwrite+=write(logfd, &line[i+nwrite], (LINE-nwrite));
            }

            // Have parent nap 1 millisecond after each line while the child reads
            //usleep(1000);

#ifdef DEBUG
            printf("PARENT:%s", line[i]);
#endif
            i++; i = i % VERSES; if(i==0) j++;


            // Wait for child, the consumer to indicate data consumed
            printf("Parent: taking syncMsg Reader semaphore\n");
            if(sem_wait(syncMsgReaderSem) < 0) perror("sem_wait syncMsgReaderSem Parent");
            printf("Parent: got syncMsg Reader semaphore\n");

        }

        // Now wait for the child to terminate

#ifdef DEBUG
        printf("Parent waiting\n");
#endif

        thisChPID = wait(&stat);
            
#ifdef DEBUG
        printf("Parent is done reciting Beowulf\n");
#endif
        close(logfd); 
        if(sem_close(syncMsgWriterSem) < 0) perror("sem_close Parent");
        if(sem_close(syncMsgReaderSem) < 0) perror("sem_close Parent");

        if(sem_unlink(syncMsgWriterSemName) < 0) perror("sem_unlink Parent");
        if(sem_unlink(syncMsgReaderSemName) < 0) perror("sem_unlink Parent");

        exit(0);

    }

}
