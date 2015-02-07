/*
** malloc_handler.c for malloc_handler in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Sat Feb  7 05:19:21 2015 THOMAS MILOX
** Last update Sat Feb  7 05:44:27 2015 THOMAS MILOX
*/

#include "malloc.h"

size_t           resize_memory_handler()
{
  size_t            check;
  t_memory_chunk    *tmp;

  check = 0;
  tmp = g_memory_map;
  while (tmp && tmp->next)
    {
      check += (tmp->size + HEADER_SIZE);
      tmp = tmp->next;
    }
  check += (tmp->size + HEADER_SIZE);
  return (check);
}

void 			      *split_memory_chunk(t_memory_chunk *tmp, size_t size)
{
  size_t 					    bckp;
  t_memory_chunk 			*_new;

  printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
  bckp = tmp->size;
  tmp->size = size;
  _new = (t_memory_chunk *)(((void *)tmp) + (tmp->size + HEADER_SIZE));
  _new->address = (((void *)_new) + HEADER_SIZE);
  _new->size = bckp - size;
  _new->_free = 0;
  _new->map_size = g_memory_map->map_size;
  _new->magic_nbr = 1123581321;
  _new->next = tmp->next;
  _new->prev = tmp;
  tmp->next->prev  = _new;
  tmp->next = _new;
  // pthread_mutex_unlock(&mutex);
  printf("4 address %p  size asked %lu\n", (tmp->next)->address, size);
  return ((tmp->next)->address);
}
