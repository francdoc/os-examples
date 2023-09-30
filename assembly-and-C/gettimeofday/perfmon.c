#include <stdio.h>
#include <unistd.h>

// Uses totally portable gettimeofday to time code sequences
// instead of the TSC.
//
// Unlike TSC, this code can be used on architectures which 
// do not include a PMU (e.g. the Beagle xM running Angstrom Linux)
//

#include "perflib.h"
#include "fib.h"

UINT32 idx = 0, jdx = 1;
UINT64 seqIterations = FIB_LIMIT_FOR_32_BIT;
UINT64 reqIterations = 1, Iterations = 100;
UINT64 fib = 0, fib0 = 0, fib1 = 1;

double DT=0.0, startTOD=0.0, stopTOD=0.0;

int main( int argc, char *argv[] )
{
   double clkRate = 1000000000.0; /* TI-OMAP3 on Beagle xM is by default 1GhZ */
   double fibCPI = 0.0;
   UINT64 instCnt = 0, cycleCnt = 0;


   if(argc == 2)
   {
      sscanf(argv[1], "%llu", &reqIterations);

      seqIterations = reqIterations % FIB_LIMIT_FOR_32_BIT;
      Iterations = reqIterations / seqIterations;
      printf("request=%llu, seqIter=%llu, iter=%llu, total=%llu, Diff=%lld\n",
             reqIterations, seqIterations, Iterations, (seqIterations*Iterations), (reqIterations - (seqIterations*Iterations)));

   }
   else if(argc == 1)
      printf("Using defaults\n");
   else
      printf("Usage: fibtest [Num iterations]\n");


   // Estimate accuracy of gettimeofday and usleep
   startTOD=readTOD();
   usleep(1000000);
   stopTOD=readTOD();
   DT = elapsedTOD(stopTOD, startTOD);
   printf("Should have slept for exactly 1 sec, DT=%lf\n", DT);
   elapsedTODPrint(stopTOD, startTOD);


   printf("\nRunning Fibonacci(%llu) Test for %llu iterations\n",
          seqIterations, Iterations);


   // START Timed Fibonacci Test
   startTOD=readTOD();
   FIB_TEST(seqIterations, Iterations);
   stopTOD=readTOD();
   // END Timed Fibonacci Test

   DT = elapsedTOD(stopTOD, startTOD);
   printf("Fibbonacci test run in DT=%.16f microsecs\n", (DT*1000000.0));
   printf("\nFibonacci(%llu)=%llu\n", seqIterations, fib);

   instCnt = (INST_CNT_FIB_INNER * seqIterations) +
             (INST_CNT_FIB_OUTTER * Iterations) + 1;

   cycleCnt = (UINT32)(clkRate * DT);

   printf("\nInst Count=%llu\n", instCnt);
   fibCPI = ((double)cycleCnt) / ((double)instCnt);
   printf("\nCPI=%4.2f\n", fibCPI);

}
