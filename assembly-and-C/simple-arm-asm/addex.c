#include <stdlib.h>

int f, g, h;

int main(void)
{
  g=0x0000DDDD;
  h=0x00001111;
  f = g + h;

  exit(1);
}
