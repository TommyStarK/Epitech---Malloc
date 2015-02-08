/*
** malloc.c for malloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:42:14 2015 THOMAS MILOX
** Last update Sat Feb  7 05:44:16 2015 THOMAS MILOX
*/

#include "malloc.h"

t_memory_chunk 				*g_memory_map = NULL;

/*
**
*/
void            *malloc(size_t size)
{
  size_t          _size;

  if ((size >> 63 == 1) && ((int64_t)size <= 0))
    {
      errno = ENOMEM;
      return NULL;
    }
  _size = ALIGN(size);
  if (!g_memory_map)
    return (init_memory_map(_size));
  return (add_new_chunk_memory(_size));
}

void            *init_memory_map(size_t size)
{
  size_t          ret;

  ret = MAP_SIZE;
  while ((size + HEADER) >= ret)
    ret += MAP_SIZE;
  if ((g_memory_map = (t_memory_chunk *)sbrk(ret)) == (void *)-1)
    return (NULL);
  g_memory_map->address = (void *)((size_t)g_memory_map + HEADER);
  g_memory_map->size = size;
  g_memory_map->_free = 0;
  g_memory_map->map_size = ret;
  g_memory_map->magic_nbr = 1123581321;
  g_memory_map->next = NULL;
  g_memory_map->prev = NULL;
  return ((void *)((size_t)g_memory_map + HEADER));
}

void            *add_new_chunk_memory(size_t size)
{
  size_t          check;
  t_memory_chunk  *tmp;

  check = 0;
  tmp = g_memory_map;
  while (tmp)
    {
      check += (tmp->size + HEADER);
      tmp = tmp->next;
    }
  if ((check + size + HEADER) >= g_memory_map->map_size)
    return (resize_memory_map(size));
  return (set_new_chunk_memory(size));

}

void 						*set_new_chunk_memory(size_t size)
{ 
  t_memory_chunk 	*tmp;

  tmp = g_memory_map;
  while (tmp && tmp->next)
    {
      if ((tmp->size >= size + HEADER) 
        && tmp->_free == 1 && tmp->magic_nbr == 1123581321)
        return (split_memory_chunk(tmp, size));
      tmp = tmp->next;
    }
  tmp->next = (t_memory_chunk *)((size_t)tmp->address + tmp->size);
  tmp->next->address = (void *)((size_t)tmp->address + tmp->size + HEADER);
  tmp->next->size = size;
  tmp->next->_free = 0;
  tmp->next->map_size = 0;
  tmp->next->magic_nbr = 0;
  tmp->next->prev = tmp;
  tmp->next->next = NULL;
  return ((void *)((size_t)tmp->next + HEADER));
}

void            *resize_memory_map(size_t size)
{
  size_t         ret;
  size_t         check;
  t_memory_chunk *tmp;

  tmp = g_memory_map;
  ret = g_memory_map->map_size;
  check = resize_memory_handler();
  while (tmp && tmp->next)
    tmp = tmp->next;
  while ((size + HEADER + check) >= g_memory_map->map_size)
    g_memory_map->map_size += MAP_SIZE;
  if (sbrk(g_memory_map->map_size - ret) == (void *)-1)
    return (NULL);
  tmp->next = (t_memory_chunk *)((size_t)tmp->address + tmp->size);
  tmp->next->address = (void *)((size_t)tmp->address + tmp->size + HEADER);
  tmp->next->size = size;
  tmp->next->_free = 0;
  tmp->next->map_size = g_memory_map->map_size;
  tmp->next->magic_nbr = 1123581321;
  tmp->next->next = NULL;
  tmp->next->prev = tmp;
  return ((void *)((size_t)tmp->next + HEADER));
}