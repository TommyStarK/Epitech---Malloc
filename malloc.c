/*
** malloc.c for malloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
1;2802;0c**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
1;2802;0c**
** Started on  Thu Feb  5 14:42:14 2015 THOMAS MILOX
** Last update Tue Feb 10 17:47:06 2015 Emmanuel Chambon
*/

#include "malloc.h"

t_memory_chunk 				*g_memory_map = NULL;
t_memory_chunk				*g_memory_freed = NULL;

/*
**
*/
void            *malloc(size_t size)
{
  size_t          _size;

  if ((size >> 48 == 1) && ((int64_t)size < 0))
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
  g_memory_map->_free = FALSE;
  g_memory_map->map_size = ret;
  g_memory_map->a_size  = (size + HEADER);
  g_memory_map->last = g_memory_map;
  g_memory_map->next = NULL;
  g_memory_map->prev = NULL;
  g_memory_map->next_freed = NULL;
  g_memory_map->prev_freed = NULL;
  g_memory_map->last_freed = NULL;
  return ((void *)((size_t)g_memory_map + HEADER));
}

void            *add_new_chunk_memory(size_t size)
{
  t_memory_chunk  *tmp;

  tmp = g_memory_freed;
  while (tmp)
    {
      //      printf("%p\n", tmp);
      if ((tmp->size >= size) && tmp->_free == TRUE)
        return (split_memory_chunk(tmp, size));
      tmp = tmp->next_freed;
    }
  if ((g_memory_map->a_size + size + HEADER) >= g_memory_map->map_size)
    return (resize_memory_map(size));
  return (set_new_chunk_memory(size));

}

void 						*set_new_chunk_memory(size_t size)
{
  t_memory_chunk				*tmp;

  tmp = g_memory_map->last;
  tmp->next = (t_memory_chunk *)((size_t)tmp->address + tmp->size);
  tmp->next->address = (void *)((size_t)tmp->address + tmp->size + HEADER);
  tmp->next->size = size;
  tmp->next->_free = FALSE;
  tmp->next->map_size = 0;
  tmp->next->prev = tmp;
  tmp->next->next = NULL;
  tmp->next->next_freed = NULL;
  tmp->next->last_freed = NULL;
  tmp->next->prev_freed = NULL;
  g_memory_map->a_size += (size + HEADER);
  g_memory_map->last = tmp->next;
  return ((void *)((size_t)tmp->next + HEADER));
}

void            *resize_memory_map(size_t size)
{
  size_t         ret;
  t_memory_chunk *tmp;

  tmp = g_memory_map->last;
  ret = g_memory_map->map_size;
  while ((size + HEADER + g_memory_map->a_size) >= g_memory_map->map_size)
    g_memory_map->map_size += MAP_SIZE;
  if (sbrk(g_memory_map->map_size - ret) == (void *)-1)
    return (NULL);
  tmp->next = (t_memory_chunk *)((size_t)tmp->address + tmp->size);
  tmp->next->address = (void *)((size_t)tmp->address + tmp->size + HEADER);
  tmp->next->size = size;
  tmp->next->_free = FALSE;
  tmp->next->map_size = g_memory_map->map_size;
  tmp->next->next = NULL;
  tmp->next->prev = tmp;
  tmp->next->next_freed = NULL;
  tmp->next->last_freed = NULL;
  tmp->next->prev_freed = NULL;
  g_memory_map->a_size += (size + HEADER);
  g_memory_map->last = tmp->next;
  return ((void *)((size_t)tmp->next + HEADER));
}
