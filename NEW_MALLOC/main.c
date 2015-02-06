
#include "malloc.h"
#include <stdio.h>

int main()
{
  char		*s = NULL;
  char		*test = NULL;
  char		*fdp = NULL;

  printf("########## %p\n", (my_malloc(1000000)));
  int i = 0;
  printf("\n############################################################\n\n");
  while (i < 50)
    {
      printf("FIRST addr n° %d = %p\n", i, (my_malloc(1500)));
      ++i;
    }
  i = 0;
  while (i < 50)
    {
      printf("SECOND addr n° %d = %p\n", i, (my_malloc(15000)));
      ++i;
    }
  i = 0;
  s = my_malloc(50);
  printf("\n        MAIN~;START\n\n");
  printf("Malloc %d: %p\n", i++, s);
  test = my_malloc(2500);
  printf("Malloc %d: %p\n", i++, test);
  fdp = my_malloc(1234567);
  printf("Malloc %d: %p\n", i++, fdp);
  printf("\n###########################################################\n\n");
  printf("\n ~~~~~~~~ SHOW MEM ALLOC ~~~~~~~~~\n\n");
  show_alloc_mem();
  printf("\n###########################################################\n\n");
  printf("\n        MAIN~END\n\n");
  return 0;
}
