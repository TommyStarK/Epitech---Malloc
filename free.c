/*
** free.c for free in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:24 2015 THOMAS MILOX
** Last update Tue Feb 10 10:23:25 2015 Emmanuel Chambon
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

void			    free_memory_chunk(void *ptr)
{
  /* if (((t_memory_chunk *)((size_t)ptr - HEADER)) == g_memory_map->last) */
  /*   brk(((t_memory_chunk *)((size_t)ptr - HEADER))); */
  ((t_memory_chunk *)((size_t)ptr - HEADER))->_free = TRUE;
  ((t_memory_chunk *)((size_t)ptr - HEADER))->next_freed = NULL;
  if (g_memory_freed == NULL)
    {
      g_memory_freed = ((t_memory_chunk *)((size_t)ptr - HEADER));
      g_memory_map->last_freed = ((t_memory_chunk *)((size_t)ptr - HEADER));
    }
  else
    g_memory_map->last_freed->next_freed = ((t_memory_chunk *)((size_t)ptr - HEADER));
}

void                        free(void *ptr)
{
  if (!ptr)
    return;
  /* if (((t_memory_chunk *)((size_t)ptr - HEADER))->_free == TRUE) */
  /*   raise(SIGABRT); */
  free_memory_chunk(ptr);
}
