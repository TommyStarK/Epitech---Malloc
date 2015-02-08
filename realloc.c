/*
** realloc.c for realloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:19 2015 THOMAS MILOX
** Last update Sun Feb  8 19:12:17 2015 Emmanuel Chambon
*/

#include "malloc.h"

void 					*realloc(void *ptt, size_t size)
{
  void *ptr;

  printf("REALLOC !!!\n");
  if (!(ptr = malloc(size)))
    return (NULL);
  ptt = ((void *)ptt) - HEADER;
  printf("REALLOC milieu %lu\n!!!\n", ((t_memory_chunk *)ptt)->size);
  memcpy(ptr, ptt, ((t_memory_chunk *)ptt)->size);
  printf("REALLOC find !!!\n");
  return ptr;
}
