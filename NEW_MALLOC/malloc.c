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
pthread_mutex_t 			mutex = PTHREAD_MUTEX_INITIALIZER;

/*
**
*/
void            *malloc(size_t size)
{
  size_t          _size;

  // pthread_mutex_lock(&mutex);
  if ((int64_t)size <= 0)
    return NULL;
  _size = ALIGN_SIZE(size);
  if (!g_memory_map)
    return (init_memory_map(_size));
  return (add_new_chunk_memory(_size));
}

void            *init_memory_map(size_t size)
{
  size_t          ret;

  ret = MAP_SIZE;
  while ((size + HEADER_SIZE) >= ret)
    ret += MAP_SIZE;
  if ((g_memory_map = (t_memory_chunk *)sbrk(ret)) == (void *)-1)
    return (NULL);
  g_memory_map->address = (((void *)g_memory_map) + HEADER_SIZE);
  g_memory_map->size = size;
  g_memory_map->_free = 0;
  g_memory_map->map_size = ret;
  g_memory_map->magic_nbr = 1123581321;
  g_memory_map->_break = sbrk(0);
  g_memory_map->next = NULL;
  g_memory_map->prev = NULL;
  // pthread_mutex_unlock(&mutex);
  return (g_memory_map->address);
}

void            *add_new_chunk_memory(size_t size)
{
  size_t          check;
  t_memory_chunk  *tmp;

  check = 0;
  tmp = g_memory_map;
  while (tmp && tmp->next)
    {
      check += (tmp->size + HEADER_SIZE);
      tmp = tmp->next;
    }
  check += (tmp->size + HEADER_SIZE);
  if ((check + size + HEADER_SIZE) >= g_memory_map->map_size)
    return (resize_memory_map(size));
  return (set_new_chunk_memory(size));

}

void 						*set_new_chunk_memory(size_t size)
{ 
  static int i = 0;
  t_memory_chunk 	*tmp;

  tmp = g_memory_map;
  while (tmp && tmp->next)
    {
      if ((tmp->size >= size + HEADER_SIZE) 
        && tmp->_free == 1 && tmp->magic_nbr == 1123581321)
        return (split_memory_chunk(tmp, size));
      tmp = tmp->next;
    }
  if ((tmp->size >= size + HEADER_SIZE) 
    && tmp->_free == 1 && tmp->magic_nbr == 1123581321)
     return (split_memory_chunk(tmp, size));
  tmp->next = (t_memory_chunk *)(((void *)tmp->address) + tmp->size);
  printf("TEST SIGSEV SUR TMP->NEXT->ADDRESS n° %i  tmp->next (%p) tmp->address (%p) tmp->size (%lu)\n",
           i++, tmp->next, tmp->address, tmp->size);
  (tmp->next)->address = (((void *)tmp->address) + (tmp->size + HEADER_SIZE));
  printf("~~~~~~~~\n");
  (tmp->next)->size = size;
  (tmp->next)->_free = 0;
  (tmp->next)->map_size = g_memory_map->map_size;
  (tmp->next)->magic_nbr = 1123581321;
  printf("%p - %p  :  %p\n", tmp->next, tmp->next->prev, tmp);
  (tmp->next)->prev = tmp;
  (tmp->next)->next = NULL;
  // pthread_mutex_unlock(&mutex);
  return ((tmp->next)->address);
}

void            *resize_memory_map(size_t size)
{
  size_t         ret;
  size_t         check;
  t_memory_chunk *tmp;

  tmp = g_memory_map;
  ret = g_memory_map->map_size;
  check = resize_memory_handler();
  while ((size + HEADER_SIZE + check) >= g_memory_map->map_size)
    g_memory_map->map_size += MAP_SIZE;
  if (sbrk(g_memory_map->map_size - ret) == (void *)-1)
    return (NULL);
  while (tmp && tmp->next)
    tmp = tmp->next;
  tmp->next = (t_memory_chunk *)(((void *)tmp->address) + tmp->size);
  (tmp->next)->address = (((void *)tmp->address) + (tmp->size + HEADER_SIZE));
  (tmp->next)->size = size;
  (tmp->next)->_free = 0;
  (tmp->next)->map_size = g_memory_map->map_size;
  (tmp->next)->magic_nbr = 1123581321;
  g_memory_map->_break = sbrk(0);
  (tmp->next)->next = NULL;
  (tmp->next)->prev = tmp;
  // pthread_mutex_unlock(&mutex);
  return ((tmp->next)->address);
}