/*
** tools.c for tools in /home/loxmi/Dropbox/Malloc/PSU_2014_malloc
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Sun Feb 15 00:03:26 2015 THOMAS MILOX
** Last update Sun Feb 15 00:03:34 2015 THOMAS MILOX
*/

#include "malloc.h"

void                        show_alloc_mem()
{
  size_t      chunk;
  t_memory_chunk    *tmp;

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