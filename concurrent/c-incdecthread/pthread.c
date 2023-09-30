#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>

#define COUNT  10

typedef struct
{
    int threadIdx;
} threadParams_t;


// POSIX thread declarations and scheduling attributes
//
pthread_t threads[2];
threadParams_t threadParams[2];


// Unsafe global
int gsum=0;

void *incThread(void *threadp)
{
    int i;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    for(i=0; i<COUNT; i++)
    {
        gsum++;
        printf("Increment thread idx=%d, gsum=%d\n", threadParams->threadIdx, gsum);
    }
}


void *decThread(void *threadp)
{
    int i;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    for(i=0; i<COUNT; i++)
    {
        gsum--;
        printf("Decrement thread idx=%d, gsum=%d\n", threadParams->threadIdx, gsum);
    }
}




int main (int argc, char *argv[])
{
   int rc;
   int i=0;

   // Create the INCREMENT THREAD
   threadParams[i].threadIdx=i;
   pthread_create(&threads[i],               // pointer to thread descriptor
                  (void *)0,                 // use default attributes
                  incThread,                 // thread function entry point
                  (void *)&(threadParams[i]) // parameters to pass in
                 );
   i++;

   // Create the DECREMENT THREAD
   threadParams[i].threadIdx=i;
   pthread_create(&threads[i],               // pointer to thread descriptor
                  (void *)0,                 // default attributes
                  decThread,                 // thread function entry point
                  (void *)&(threadParams[i]) // parameters
                 );

   // JOIN BOTH INCREMENT and DECREMENT THREAD
   for(i=0; i<2; i++)
     pthread_join(threads[i], NULL);

   printf("TEST COMPLETE\n");
}
