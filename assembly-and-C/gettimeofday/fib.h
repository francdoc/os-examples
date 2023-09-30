#ifndef _FIB_H_
#define _FIB_H_

#define FIB_LIMIT_FOR_32_BIT 47

#define INST_CNT_FIB_INNER 15
#define INST_CNT_FIB_OUTTER 6


#define FIB_TEST(seqCnt, iterCnt)      \
   for(idx=0; idx < iterCnt; idx++)    \
   {                                   \
      fib = fib0 + fib1;               \
      while(jdx < seqCnt)              \
      {                                \
         fib0 = fib1;                  \
         fib1 = fib;                   \
         fib = fib0 + fib1;            \
         jdx++;                        \
      }                                \
   }                                   \

#endif
