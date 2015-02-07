
#include "malloc.h"
#include <stdio.h>

int main()
{
  char		*s = NULL;
  char		*test = NULL;
  char		*fdp = NULL;

  /* printf("%p\n", my_malloc(150000000000)); */
  int i = 0;
  printf("%p\n", my_malloc(40000000));
  printf("\n############################################################\n\n");
  while (i < 51)
    {
      printf("n° %d = %p\n", i, (my_malloc(1500)));
      ++i;
    }
  i = 0;
  while (i < 51)
    {
      printf("SECOND addr n° %d = %p\n", i, (my_malloc(1500000000)));
      ++i;
    }
  s = my_malloc(50);
  printf("\n        MAIN~;START\n\n");
  printf("Malloc: %p\n", s);
  test = my_malloc(2500);
  printf("Malloc: %p\n", test);
  fdp = my_malloc(1234567);
  printf("Malloc: %p\n", fdp);
  printf("\n###########################################################\n\n");
  printf("\n ~~~~~~~~ SHOW MEM ALLOC ~~~~~~~~~\n\n");
  show_alloc_mem();
  printf("\n###########################################################\n\n");
  printf("\n        MAIN~END\n\n");
  return 0;
}
