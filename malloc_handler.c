/*
** malloc_handler.c for malloc_handler in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Sat Feb  7 05:19:21 2015 THOMAS MILOX
** Last update Tue Feb 10 10:22:01 2015 Emmanuel Chambon
*/

#include "malloc.h"

void 			      *split_memory_chunk(t_memory_chunk *tmp, size_t size)
{
  size_t 					    bckp;
  t_memory_chunk 			*_new;

  printf("split \n");
  usleep(0.5);
  bckp = tmp->size;
  tmp->size = size;
  _new = (t_memory_chunk *)((size_t)tmp + HEADER + tmp->size);
  _new->address = (void *)((size_t)_new + HEADER);
  _new->size = bckp - size;
  _new->_free = 0;
  _new->map_size = g_memory_map->map_size;
  _new->next = tmp->next;
  _new->prev = tmp;
  tmp->next->prev  = _new;
  tmp->next = _new;
  return ((void *)((size_t)tmp->next + HEADER));
}
