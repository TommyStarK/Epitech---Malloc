/*
** malloc_handler.c for malloc_handler in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Sat Feb  7 05:19:21 2015 THOMAS MILOX
** Last update Wed Feb 11 08:01:38 2015 THOMAS MILOX
*/

#include "malloc.h"

void				        *split_memory_chunk(t_memory_chunk **current, size_t size)
{
  size_t				bckp;
  t_memory_chunk			*tmp;
  t_memory_chunk			*_new;

  tmp = *current;
  // printf("tmp :%p\n", tmp);
  bckp = tmp->n_size;
  // printf("bckp : %lu\n", bckp);
  tmp->_free = FALSE;
  tmp->size = size;
  _new = (t_memory_chunk *)((void *)tmp->address + size);
  _new->address = (void *)((void *)_new + HEADER);
  // printf("_new->address %p\n", _new->address);
  _new->size = bckp - size;
  _new->_free = TRUE;
  _new->next = tmp->next;
  _new->prev = tmp;
  _new->next_freed = tmp->next_freed;
  _new->prev_freed = tmp->prev_freed;
  tmp->next = _new;
  g_memory_map->last = (tmp == g_memory_map->last ? _new : g_memory_map->last);
  g_memory_freed->last_freed =
    (tmp == g_memory_freed->last_freed ? _new : g_memory_freed->last_freed);
  return ((*current)->address);
}
