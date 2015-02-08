/*
** realloc.c for realloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:19 2015 THOMAS MILOX
** Last update Sun Feb  8 20:36:23 2015 Emmanuel Chambon
*/

#include "malloc.h"

void 					*realloc(void *ptt, size_t size)
{
  void *ptr = malloc(size);
  if (!ptt)
    return ptr;
  void *tmp = ((void *)ptt) - HEADER;
  ptt = memcpy(ptr, ptt, ((t_memory_chunk *)(tmp))->size);
  return ptr;
}
