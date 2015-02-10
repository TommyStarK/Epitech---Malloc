
#include "malloc.h"
#include <stdio.h>

int main()
{
  char *toto = malloc(10);
  char *tata = malloc(10);
  char *titi = malloc(10);
  char *tutu = malloc(10);


  show_alloc_mem();
  sleep(3);
  free(toto);
  free(tata);
  show_alloc_mem();
  sleep(3);
  char tyty = malloc(10);
  show_alloc_mem();
  return 0;
}
