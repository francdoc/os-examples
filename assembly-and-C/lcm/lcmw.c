#include "lcmw.h"


int main(void)
{
    int a=146, b=18, gcd=0, lcm=0;

    gcd=gcdc(a,b);
    printf("C gcd(%d, %d)=%d\n", a, b, gcd);
    lcm=lcmc(a,b);
    printf("C lcm(%d, %d)=%d\n", a, b, lcm);
}
