/*
** malloc_handler.c for malloc_handler in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Sat Feb  7 05:19:21 2015 THOMAS MILOX
** Last update Tue Feb 10 17:43:34 2015 Emmanuel Chambon
*/

#include "malloc.h"

void				*split_memory_chunk(t_memory_chunk *tmp, size_t size)
{
  t_memory_chunk		*new;
  size_t			s;

  printf("split\n");
  tmp->_free = FALSE;
  if (tmp->size == size)
    return ((void *)((size_t)tmp + HEADER));
  else if (tmp->size >= (size + HEADER + 8))
    {
      s = tmp->size;
      tmp->size = size;
      new = ((void *)tmp) + HEADER + size;
      new->size = s - HEADER - size;
      new->address = ((void *)new) + HEADER;
      new->_free = TRUE;
      new->next = tmp->next;
      new->prev = tmp;
      tmp->next = new;
      new->next_freed = tmp->next_freed;
      new->prev_freed = tmp->prev_freed;
      if (new->next_freed)
	new->next_freed->prev_freed = new;
      if (new->prev_freed)
	new->prev_freed->next_freed = new;
      if (g_memory_map->last_freed == tmp)
	g_memory_map->last_freed = new;
    }
  return ((void *)((size_t)tmp + HEADER));
}
