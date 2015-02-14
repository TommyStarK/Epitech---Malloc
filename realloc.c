/*
** realloc.c for realloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:19 2015 THOMAS MILOX
** Last update Wed Feb 11 06:17:11 2015 THOMAS MILOX
*/

#include "malloc.h"

void 						*resize_end(void *ptr, size_t size)
{
	size_t 					ret;
	t_memory_chunk 			*current;

	ret = g_memory_map->map_size;
	current = (t_memory_chunk *)((void *)ptr - HEADER);
	while ((g_memory_map->a_size + size) >= g_memory_map->map_size)
		g_memory_map->map_size += MAP_SIZE;
	if (sbrk(g_memory_map->map_size - ret) == (void *)-1)
		return (NULL);
	current->size += size;
	return (ptr);
}

void 						*realloc_in_new_chunk(void *ptr, size_t size,
													 t_memory_chunk *current)
{
	t_memory_chunk	 		*chunk;

	if (current == g_memory_map->last)
	{
		if ((g_memory_map->a_size + size) >= g_memory_map->map_size)
			return (resize_end(ptr, size));
		current->size += size;
		g_memory_map->a_size += size;
	}
	else if (current->next && current->next->_free == TRUE 
			&& (current->size + current->next->n_size + HEADER >= size))
	{
		chunk = current->next;
		chunk->_free = FALSE;
		chunk->next_freed = 
			(chunk->next_freed ? chunk->next_freed->next_freed : NULL);
		chunk->prev_freed = 
			(chunk->prev_freed ? chunk->prev_freed->prev_freed : NULL);
		g_memory_freed->last = 
			(chunk->next_freed == g_memory_freed->last ? chunk->next_freed : g_memory_freed->last);
		current->size = size;
		current->next = chunk->next;
	}
	else
	{
		if (!(chunk = malloc(size)))
			return (NULL);
		if (size < ((t_memory_chunk *)(ptr - HEADER))->size)
			memcpy((void *)chunk, ptr, size);
		else
			memcpy((void *)chunk, ptr, ((t_memory_chunk *)(ptr - HEADER))->size);
		free(ptr);
		return ((void *)chunk);
	}
	return (ptr);
}

void 						*realloc(void *ptr, size_t size)
{
	size_t 					new_size;
	t_memory_chunk 			*current;

	if (!ptr)
		return (malloc(size));
	if ((size >> 48 >= 1) || !size)
	{
		return (NULL);
		// free(ptr);
		// return (malloc(size));
	}
	new_size = ALIGN(size);
	current = (t_memory_chunk *)((void *)ptr - HEADER);
	if (current->size == new_size)
		return (ptr);
	return (realloc_in_new_chunk(ptr, new_size, current));
}