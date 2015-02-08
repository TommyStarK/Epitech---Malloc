/*
** free.c for free in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:24 2015 THOMAS MILOX
** Last update Thu Feb  5 14:41:25 2015 THOMAS MILOX
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
    }}

void                        merge_memory_chunks()
{
}

void                        clean_memory_map()
{
  t_memory_chunk            *prev;
  t_memory_chunk            *tmp;


  tmp = g_memory_map;
  while (tmp && tmp->next)
    tmp = tmp->next;
  prev = tmp->prev;
  if (tmp->_free == 1 && prev)
  {
    // tmp->address = NULL;
    if (brk(tmp) == -1)
      return;
    prev->next = NULL;
    clean_memory_map();
  }
  merge_memory_chunks();
}

void                        free(void *ptr)
{
  t_memory_chunk            *tmp;

  tmp = g_memory_map;
  if (!ptr || !tmp)
    return;
  if (!tmp->next)
  {
    if (g_memory_map->address == ptr && g_memory_map->magic_nbr == 1123581321)
      if (brk(g_memory_map) == -1)
        raise(SIGBUS);
    g_memory_map->address = NULL;
    g_memory_map = NULL;
  }
  else
  {
    while (tmp->address != ptr)
      tmp = tmp->next;
    if (tmp->address == ptr && tmp->magic_nbr == 1123581321)
    {
      tmp->_free = 1;
      // tmp->address = NULL;
      clean_memory_map();
    }
  }
}