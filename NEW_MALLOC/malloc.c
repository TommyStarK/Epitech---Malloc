/*
** malloc.c for malloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:42:14 2015 THOMAS MILOX
** Last update Fri Feb  6 22:18:37 2015 THOMAS MILOX
*/

#include "malloc.h"

t_memory_chunk 				*g_memory_map = NULL;
pthread_mutex_t 			mutex = PTHREAD_MUTEX_INITIALIZER;

/*
**
*/

void 						*resize_memory_map(size_t size)
{
  size_t 					check;
  t_memory_chunk 			*tmp;

  check = 0;
  tmp = g_memory_map;
  while (tmp && tmp->next)
    {
      check += (tmp->size + HEADER_SIZE);
      tmp = tmp->next;
    }
  check += (tmp->size + HEADER_SIZE);
  printf("check : %lu  map_size : %lu\n", check, g_memory_map->map_size);
  while ((size + HEADER_SIZE + check) >= g_memory_map->map_size)
    g_memory_map->map_size += MAP_SIZE;
  printf("new g_memory_map_size : [%lu]\n", g_memory_map->map_size);
  if (sbrk(g_memory_map->map_size) == (void *)-1)
    {
      printf("TEEEEEEEEEEEEEEESSSSSSSSSSSST     22222\n");
      return (NULL);
    }
  tmp->next = (t_memory_chunk *)(((void *)tmp->address) + tmp->size);
  (tmp->next)->address = (((void *)tmp->address) + tmp->size + HEADER_SIZE);
  (tmp->next)->size = size;
  (tmp->next)->_free = 0;
  (tmp->next)->map_size = g_memory_map->map_size;
  (tmp->next)->magic_nbr = 1123581321;
  g_memory_map->_break = sbrk(0);
  (tmp->next)->next = NULL;
  (tmp->next)->prev = tmp;
  pthread_mutex_unlock(&mutex);
  return (tmp->next->address);
}

void 						*split_memory_chunk(t_memory_chunk *tmp, size_t size)
{
  size_t 					bckp;
  t_memory_chunk 			*_new;

  bckp = tmp->size;
  tmp->size = size;
  _new = (t_memory_chunk *)(tmp + tmp->size + HEADER_SIZE);
  _new->address = (((void *)_new) + HEADER_SIZE);
  _new->size = bckp - size;
  _new->_free = 0;
  _new->map_size = g_memory_map->map_size;
  _new->magic_nbr = 1123581321;
  _new->next = tmp->next;
  _new->prev = tmp;
  tmp->next->prev  = _new;
  tmp->next = _new;
  pthread_mutex_unlock(&mutex);
  return ((tmp->next)->address);
}

void 						*set_new_block_memory(size_t size)
{
  size_t 					check;
  t_memory_chunk 	*tmp;

  tmp = g_memory_map;
  check = 0;
  while (tmp && tmp->next)
    {
      check += (tmp->size + HEADER_SIZE);
      tmp = tmp->next;
    }
  check += (tmp->size + HEADER_SIZE);
  if (g_memory_map->map_size <= (check + size + HEADER_SIZE))
    return (resize_memory_map(size));
  tmp->next = (t_memory_chunk *)(tmp->address + tmp->size);
  (tmp->next)->address = (((void *)tmp->address) + tmp->size + HEADER_SIZE);
  (tmp->next)->size = size;
  (tmp->next)->_free = 0;
  (tmp->next)->map_size = g_memory_map->map_size;
  (tmp->next)->magic_nbr = 1123581321;
  g_memory_map->_break = sbrk(0);
  (tmp->next)->next = NULL;
  (tmp->next)->prev = tmp;
  pthread_mutex_unlock(&mutex);
  return ((tmp->next)->address);
}

void 						*add_new_chunk_memory(size_t size)
{
  size_t 					check;
  t_memory_chunk 	*tmp;

  check = 0;
  tmp = g_memory_map;
  while (tmp && tmp->next)
    {
      check += (tmp->size + HEADER_SIZE);
      tmp = tmp->next;
    }
  check += tmp->size + HEADER_SIZE;
  if ((check + size + HEADER_SIZE) >= g_memory_map->map_size)
    {
    printf("TEEEEEEEEEEEEEEESSSSSSSSSSSST   111111\n");
    return (resize_memory_map(size));
    }
  return (set_new_block_memory(size));
}

/*
**
*/

void 						*init_memory_map(size_t size)
{
  size_t 					ret;

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
  pthread_mutex_unlock(&mutex);
  return (g_memory_map->address);
}

void 						*my_malloc(size_t size)
{
  size_t 					_size;

  pthread_mutex_lock(&mutex);
  if ((int64_t)size <= 0)
    return NULL;
  	_size = ALIGN_SIZE(size + HEADER_SIZE);
  if (!g_memory_map)
    return (init_memory_map(_size));
  return (add_new_chunk_memory(_size));
}