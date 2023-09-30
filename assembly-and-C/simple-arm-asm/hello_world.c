#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char msg[]="Hellow, ARM!\n";

int main(void)
{
    write(1, msg, sizeof(msg));
    exit(0);
}
