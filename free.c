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
  size_t                  data;
  t_memory_chunk          *tmp;

  tmp = g_memory_map;
  printf("break : 0x%lX\n", (size_t) sbrk(0));
  while (tmp)
    {
      data = (size_t)tmp + HEADER;
      if (!tmp->_free)
          printf("0x%lX - 0x%lX : %lu bytes\n",
                  data, data + tmp->size, tmp->size);
      tmp = tmp->next;
    }
}

void                        merge_memory_chunks(void *ptr)
{
  (void)ptr;
}

void                        clean_memory_map()
{
  t_memory_chunk            *prev;
  t_memory_chunk            *tmp;


  tmp = g_memory_map->last;
  if (tmp->_free == TRUE)
  {
    while (tmp && tmp->prev && tmp->_free == TRUE)
      tmp = tmp->prev;
    prev = tmp->prev;
    if (brk(tmp) == -1)
        return;
    prev->next = NULL;
    clean_memory_map();
  }
}

void                        free(void *ptr)
{
  // return;
  if (!ptr)
    return;
  // printf("FREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
  g_memory_map->a_free = TRUE;
  ((t_memory_chunk *)((size_t)ptr - HEADER))->size = TRUE;
  // merge_memory_chunks(ptr);
  clean_memory_map();
}
