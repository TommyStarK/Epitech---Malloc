#include "malloc.h"

int main()
{
  for(int i = 0; i < 10; i++)
    printf("%p\n", malloc(800000000));
}
