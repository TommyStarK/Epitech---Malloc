/*
** realloc.c for realloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:19 2015 THOMAS MILOX
** Last update Sun Feb 15 05:21:10 2015 THOMAS MILOX
*/

#include "malloc.h"

void 						*realloc(void *old_chunk, size_t size)
{
  void						*new_chunk;

  lock_thread(1);
  if (!size || !(new_chunk = malloc(size)))
    {
      unlock_thread(1);
      if (size)
	free(old_chunk);
      return (NULL);
    }
  if (!old_chunk)
    {
      unlock_thread(1);
      return (new_chunk);
    }
  if (size < ((t_memory_chunk *)((void *)old_chunk - HEADER))->size)
    new_chunk = memcpy(new_chunk, old_chunk, size);
  else
    new_chunk = memcpy(new_chunk, old_chunk,
		       ((t_memory_chunk *)((void *)old_chunk - HEADER))->size);
  free(old_chunk);
  unlock_thread(1);
  return (new_chunk);
}
