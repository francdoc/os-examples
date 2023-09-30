#include "gcdw.h"


int main(void)
{
    int a=146, b=18, gcd=0;

    gcd=gcdc(a,b);
    printf("C gcd(%d, %d)=%d\n", a, b, gcd);
    gcd=gcda(a,b);
    printf("ASM gcd(%d, %d)=%d\n", a, b, gcd);
    gcd=gcda1(a,b);
    printf("ASM Opt-1 gcd(%d, %d)=%d\n", a, b, gcd);
    gcd=gcda2(a,b);
    printf("ASM Opt-2 gcd(%d, %d)=%d\n", a, b, gcd);
}
