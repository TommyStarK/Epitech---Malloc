#include "malloc.h"
#include <stdio.h>

int main()
{
  char		*s = NULL;
  char		*test = NULL;
  char		*fdp = NULL;

  int i = 0;
  printf("%p\n", my_malloc(1000000));
  while (i < 50)
    {
      printf("addr = %p\n", (my_malloc(100000)));
      ++i;
    }
  i = 0;
  s = my_malloc(50);
  printf("\n        MAIN~START\n\n");
  printf("Malloc %d: %p\n", i++, s);
  /* my_free(s); */
  /* printf("Apres free: %p    [%s]\n", s, s); */
  test = my_malloc(2500);
  printf("Malloc %d: %p\n", i++, test);
  fdp = my_malloc(1234567);
  /* my_free(test); */
  /* printf("test apres free %p\n", test); */
  /* test = my_malloc(2400); */
  /* printf("test realloue -> deja free mais plage mémoire assez grande: %p\n", test); */
  printf("Malloc %d: %p\n", i++, fdp);
  /* my_free(fdp); */
  printf("\n###########################################################\n\n");
  t_range_memory	*tmp = g_range_memory;
  while (tmp)
    {
      printf("plage: %p   -   struct info: %p   -   size: %lu\n", tmp->address, (t_range_memory *)(tmp->address + tmp->size), tmp->size);
      tmp = tmp->next;
    }
  printf("\n ~~~~~~~~ SHOW MEM ALLOC ~~~~~~~~~\n\n");
  show_alloc_mem();
  printf("\n###########################################################\n\n");
  printf("\n        MAIN~END\n\n");
  return 0;
}
