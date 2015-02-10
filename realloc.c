/*
** realloc.c for realloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:19 2015 THOMAS MILOX
** Last update Tue Feb 10 10:08:48 2015 Emmanuel Chambon
*/

#include "malloc.h"

// void 					*realloc(void *ptt, size_t size)
// {
//   void *ptr = malloc(size);
//   if (!ptt)
//     return ptr;
//   void *tmp = ((void *)ptt) - HEADER;
//   ptt = memcpy(ptr, ptt, ((t_memory_chunk *)(tmp))->size);
//   return ptr;
// }


void 					*realloc(void *old_chunk, size_t size)
{
  printf("entrée realloc\n");
  void 					*new_chunk;

  if (!(new_chunk = malloc(size)))
  	return (NULL);
  if (!old_chunk)
    return (new_chunk);
  new_chunk = memcpy(new_chunk, old_chunk,
  	((t_memory_chunk *)((size_t)old_chunk - HEADER))->size);
  // free(old_chunk);
  printf("sortie realloc\n");
  return (new_chunk);
}
