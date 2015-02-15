/*
** free.c for free in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:24 2015 THOMAS MILOX
** Last update Sun Feb 15 03:00:39 2015 THOMAS MILOX
*/

#include "malloc.h"

void                        re_position_break_in_memory()
{
  t_memory_chunk		*end;

  end = g_memory_freed->last_freed;
  if ((void *)(end->address + end->n_size) ==
      (void *)((void *)g_memory_map->last + g_memory_map->last->size))
  {
    if (end->prev)
      (end->prev)->next = NULL;
    g_memory_map->last = (end->prev != NULL ? end->prev : NULL);
    g_memory_freed->last_freed = (end->prev_freed ? end->prev_freed : NULL);
    end->next_freed = NULL;
    g_memory_map = (end == g_memory_map ? NULL : g_memory_map);
    g_memory_freed = (end == g_memory_freed ? NULL : g_memory_freed);
    if (brk(end) == -1)
      return;
  }
  return;
}

void                        merge(t_memory_chunk *current)
{
  size_t			new_size;
  t_memory_chunk		*left;
  t_memory_chunk		*right;


  left = current;
  right = current;
  new_size = (current->n_size + HEADER);
   if (current->prev && current->prev->_free == TRUE)
  {
    left = left->prev;
    new_size += (left->n_size + HEADER);
  }
  if (current->next && current->next->_free == TRUE)
  {
    right = right->next;
    new_size += (right->n_size + HEADER);
  }
  left->n_size = (new_size - HEADER);
  left->next_freed = right->next_freed;
  if (right->next_freed)
    (right->next_freed)->prev_freed = left;
  else
    g_memory_freed->last_freed = left;
  re_position_break_in_memory();
  unlock_thread(0);
}


void                        free(void *ptr)
{
  t_memory_chunk		*current;

  if (!ptr)
    return;
  lock_thread(0);
  current = (t_memory_chunk *)((void *)ptr - HEADER);
  if ((size_t)current->address % 8 != 0)
    return;
  current->_free = (current->_free == TRUE ? raise(SIGABRT) : TRUE);
  current->n_size = current->size;
  if (!g_memory_freed)
  {
    g_memory_freed = current;
    g_memory_freed->last_freed = g_memory_freed;
    g_memory_freed->next_freed = NULL;
    g_memory_freed->prev_freed = NULL;
  }
  else
  {
    current->prev_freed = g_memory_freed->last_freed;
    current->next_freed = NULL;
    (current->prev_freed)->next_freed = current;
    g_memory_freed->last_freed = current;
  }
  merge(current);
}
