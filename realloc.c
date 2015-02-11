/*
** realloc.c for realloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:19 2015 THOMAS MILOX
** Last update Tue Feb 10 17:33:36 2015 Emmanuel Chambon
*/

#include "malloc.h"

void 					*realloc(void *old_chunk, size_t size)
{
  void 					*new_chunk;

  if (!(new_chunk = malloc(size)))
  	return (NULL);
  if (!old_chunk)
    return (new_chunk);
  new_chunk = memcpy(new_chunk, old_chunk,
  	((t_memory_chunk *)((void *)old_chunk - HEADER))->size);
  //free(old_chunk);
  return (new_chunk);
}
