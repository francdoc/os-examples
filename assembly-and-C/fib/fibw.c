#include "fibw.h"

#define N (10)

int main(void)
{
    int f;

    f=fibc(N);
    printf("C code: f(%u)=%u\n", N, f);

    fiba(N);
    printf("ARM Assembly code: f(%u)=%u\n", N, f);

}
