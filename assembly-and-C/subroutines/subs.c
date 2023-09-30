#include <stdio.h>
#include <string.h>

void globalfunct(void)
{

    void localfunct(void)
    {
        printf("local function\n");
    }

    printf("global function\n");

    localfunct();
}

void main(void)
{

    globalfunct();

    // not visible here, so can't call, but global can
    // localfunct();
}
