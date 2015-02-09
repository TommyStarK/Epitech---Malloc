/*
** free.c for free in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:24 2015 THOMAS MILOX
** Last update Sun Feb  8 19:05:06 2015 Emmanuel Chambon
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

void                        merge_memory_chunks(void *ptr)
{
  (void)ptr;
}

void                        bring_back_break()
{
  t_memory_chunk            *prev;
  t_memory_chunk            *tmp;


  tmp = g_memory_map->last;
  if (tmp->_free == TRUE)
  {
    if (tmp->prev)
      g_memory_map->last = tmp->prev;
    while (tmp->prev && tmp->prev->_free == TRUE)
      tmp = tmp->prev;
    prev = tmp->prev;
    if (brk(tmp) == -1)
        return;
    if (prev)
      prev->next = NULL;
    else 
      g_memory_map = NULL;
  }
}

void                        free(void *ptr)
{
  return;
  if (!ptr)
    return;
  if (((t_memory_chunk *)((size_t)ptr - HEADER))->_free == TRUE)
    raise(SIGABRT);
  g_memory_map->a_free = TRUE;
  ((t_memory_chunk *)((size_t)ptr - HEADER))->_free = TRUE;
  // merge_memory_chunks(ptr);
  bring_back_break();
}
