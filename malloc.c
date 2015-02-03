/*
** malloc.c for Malloc in /home/loxmi/Dropbox/Malloc/v2
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Jan 29 14:57:01 2015 THOMAS MILOX
** Last update Mon Feb  2 18:51:01 2015 THOMAS MILOX
*/

#include "malloc.h"


t_range_memory 				*g_range_memory = NULL;

/*
**
*/

size_t 						align_size_4(size_t size)
{
	size_t 					ret;

	// ret = (((((size) - 1) >> 2) << 2) + 4);
	ret = (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1));
	return ret;
}

int 						check_in_free_chunks(void *new_range_memory, size_t size)
{
	t_range_memory 			*tmp;

	tmp = g_range_memory;
	while (tmp && tmp->next)
		{
			if (!tmp->flag && tmp->size > size)
				{
					tmp = (t_range_memory *)(new_range_memory + size);
					tmp->address = new_range_memory;
					tmp->size = size;
					tmp->flag = 1;
					return 1;
				}
			tmp = tmp->next;
		}
	return 0;
}

void 						add_new_range_memory(void *new_range_memory, size_t size)
{
	t_range_memory 			*_new;
	t_range_memory 			*end;

	end = g_range_memory;
	if (!check_in_free_chunks(new_range_memory, size))
		{
			while (end && end->next)
				end = end->next;
			_new = (t_range_memory *)(new_range_memory + size);
			_new->address = new_range_memory;
			_new->size = size;
			_new->flag = 1;
			_new->next = NULL;
			_new->prev = end;
			end->next = _new;
		}
}

void 						*my_malloc(size_t size)
{
	size_t 					_size;
	void 					*new_range_memory;

	new_range_memory = NULL;
	if (!size)
		return NULL;
	_size = align_size_4(size);
	if ((new_range_memory = sbrk(size + STRUCT_SIZE)) == (void *)-1)
		return NULL;
	if (!g_range_memory)
		{
			g_range_memory = (t_range_memory *)(new_range_memory + _size);
			g_range_memory->address = new_range_memory;
			g_range_memory->size = _size;
			g_range_memory->flag = 1;
			g_range_memory->prev = NULL;
			g_range_memory->next = NULL;
		}
	else
		add_new_range_memory(new_range_memory, _size);
	return (new_range_memory);
}
