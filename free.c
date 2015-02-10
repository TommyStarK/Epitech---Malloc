/*
** free.c for free in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:24 2015 THOMAS MILOX
** Last update Tue Feb 10 17:46:47 2015 Emmanuel Chambon
*/

#include "malloc.h"

void                        show_alloc_mem()
{
  size_t                  chunk;
  t_memory_chunk          *tmp;

  tmp = g_memory_map;
  printf("break : 0x%lX\n", (size_t) sbrk(0));
  while (tmp)
    {
      chunk = (size_t)tmp + HEADER;
      if (!tmp->_free)
          printf("0x%lX - 0x%lX : %lu bytes\n", chunk,
            chunk + tmp->size, tmp->size);
      tmp = tmp->next;
    }
}
void				merge(void *ptr)
{
  t_memory_chunk		*actual;

  actual = (t_memory_chunk *)(ptr - HEADER);
  if (actual->prev != NULL && actual->prev->_free == TRUE)
    {
      printf("merge prev\n");
      if (actual->prev == g_memory_map->last)
	if (g_memory_map->last->prev)
	  g_memory_map->last = g_memory_map->last->prev;
      actual->prev->size += actual->size + HEADER;
      if (actual->prev)
	actual->prev->next = actual->next;
      if (actual->next && actual->prev)
	actual->next->prev = actual->prev;
    }
  else if (actual->next != NULL && actual->next->_free == TRUE)
    {
      printf("merge next\n");
      actual->size += actual->next->size + HEADER;
      actual->next_freed = actual->next->next_freed;
      actual->prev_freed = actual->next->prev_freed;
      if (actual->prev_freed)
	actual->prev_freed->next_freed = actual;
      if (actual->next_freed)
	actual->next_freed->prev_freed = actual;
      if (actual->next && actual->next->next)
	actual->next->next->prev = actual;
      if (actual->prev)
	actual->prev->next = actual;
    }
}

void			    free_memory_chunk(void *ptr)
{
  ((t_memory_chunk *)(ptr - HEADER))->_free = TRUE;
  if ((((t_memory_chunk *)((void *)ptr - HEADER))->prev != NULL
       && ((t_memory_chunk *)((void *)ptr - HEADER))->prev->_free == TRUE)
      || (((t_memory_chunk *)((void *)ptr - HEADER))->next != NULL
	  && ((t_memory_chunk *)((void *)ptr - HEADER))->next->_free == TRUE))
    return merge(ptr);
  ((t_memory_chunk *)(ptr - HEADER))->next_freed = NULL;
  ((t_memory_chunk *)(ptr - HEADER))->prev_freed = g_memory_map->last_freed;
  if (g_memory_freed == NULL)
    {
      g_memory_freed = ((t_memory_chunk *)((size_t)ptr - HEADER));
      g_memory_map->last_freed = g_memory_freed;
    }
  else {
    g_memory_map->last_freed->next_freed = ((t_memory_chunk *)((size_t)ptr - HEADER));
    g_memory_map->last_freed = g_memory_map->last_freed->next_freed;
  }
}

void                        free(void *ptr)
{
  if (!ptr)
    return;
  if (((t_memory_chunk *)((size_t)ptr - HEADER))->_free == TRUE)
    raise(SIGABRT);
  free_memory_chunk(ptr);
}
