/*
** malloc.c for  in /home/chambo_e/epitech/PSU_2014_malloc/malloc_manu
**
** Made by Emmanuel Chambon
** Login   <chambo_e@epitech.net>
**
** Started on  Sun Feb  8 15:59:44 2015 Emmanuel Chambon
** Last update Sun Feb  8 19:01:47 2015 Emmanuel Chambon
*/

#include "malloc.h"

t_memory_chunk		*g_memory_map = NULL;

size_t			bytes_needed(size_t size)
{
  size_t		bytes;
  t_memory_chunk	*tmp;

  if (g_memory_map)
    {
      bytes = 0;
      tmp = g_memory_map;
      while (tmp)
	{
	  printf("a\n");
	  bytes += (tmp->csize + HEADER);
	  tmp = tmp->next;
	}
      return (bytes + size + HEADER);
    }
  bytes = MAP_SIZE;
  while ((size + HEADER) >= bytes)
    bytes += MAP_SIZE;
  return (bytes);
}

void			*first_fit_me_dat(size_t size, t_memory_chunk *fat_chunk)
{
  t_memory_chunk	*split;

  printf("set new split\n");
  if (fat_chunk->csize <= (size + HEADER))
    {
      fat_chunk->free = 0;
      printf("malloc sorti\n");
      return ((void *)fat_chunk->chunk);
    }
  fat_chunk->free = 0;
  split = ((void *)fat_chunk->chunk) + fat_chunk->csize;
  split->prev = fat_chunk;
  split->next = fat_chunk->next;
  if (!split->next)
    {
      g_memory_map->last = split;
      split->last = split;
    }
  fat_chunk->next = split;
  split->csize = (fat_chunk->csize - size - HEADER);
  fat_chunk->csize = size;
  split->msize = g_memory_map->msize;
  split->chunk = ((void *)split) + HEADER;
  split->free = 0;
  printf("malloc sorti\n");
  return ((void *)fat_chunk->chunk);
}

void			*set_new_chunk_memory(size_t size)
{
  t_memory_chunk	*last;
  size_t		bytes;

  printf("set new chunk\n");
  if ((bytes = bytes_needed(size)) > g_memory_map->msize)
    {
      printf("1\n");
      if ((sbrk(bytes - g_memory_map->msize)) == (void *)-1)
	{
	  errno = ENOMEM;
	  return (NULL);
	}
      g_memory_map->msize = bytes;
    }
  printf("2\n");
  last = ((void *)g_memory_map->last->chunk) + g_memory_map->last->csize;
  printf("3\n");
  printf("%p\n", g_memory_map->last);
  last->next = NULL;
  printf("4\n");
  last->prev = g_memory_map->last;
  printf("5\n");
  last->last = last;
  printf("6\n");
  g_memory_map->last = last;
  printf("7\n");
  last->csize = size;
  last->msize = g_memory_map->msize;
  last->chunk = ((void *)last) + HEADER;
  last->free = 0;
  printf("malloc sorti\n");
  return ((void *)last->chunk);
}

void			*add_new_chunk_memory(size_t size)
{
  t_memory_chunk	*tmp;

  tmp = g_memory_map;
  while (tmp)
    {
      if ((tmp->free == 1) && (tmp->csize >= size))
	return (first_fit_me_dat(size, tmp));
      tmp = tmp->next;
    }
  return (set_new_chunk_memory(size));
}

void			*init_memory_map(size_t size)
{
  size_t		bytes;

  bytes = bytes_needed(size);
  if ((g_memory_map = ((t_memory_chunk *)sbrk(bytes))) == (void *)-1)
    {
      errno = ENOMEM;
      return (NULL);
    }
  g_memory_map->prev = NULL;
  g_memory_map->next = NULL;
  g_memory_map->last = g_memory_map;
  g_memory_map->csize = size;
  g_memory_map->msize = bytes;
  g_memory_map->chunk = ((void *)g_memory_map) + HEADER;
  g_memory_map->free = 0;
  printf("malloc sorti\n");
  return ((void *)g_memory_map->chunk);
}

void			*malloc(size_t size)
{
  printf("malloc entré\n");
  if (((size >> 48) >= 1) || ((int64_t)size < 0))
    {
      errno = ENOMEM;
      return (NULL);
    }
  size = ALIGN(size);
  if (!g_memory_map)
    return (init_memory_map(size));
  return (add_new_chunk_memory(size));
}
