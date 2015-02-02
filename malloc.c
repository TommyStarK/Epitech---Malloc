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

	ret = (((((size) - 1) >> 2) << 2) + 4);
	// ret = (size + ((3) & ~(3)));
	return ret;
}

int 						check_in_free_chunks(void *new_range_memory, size_t size, int _padding)
{
	t_range_memory 			*tmp;

	tmp = g_range_memory;
	while (tmp)
		{
			if (!tmp->flag && tmp->size > size)
				{
					tmp = (t_range_memory *)(new_range_memory + size);
					tmp->address = new_range_memory;
					tmp->size = size;
					tmp->flag = 1;
					tmp->padding = _padding;
					return 1;
				}
			tmp = tmp->next;
		}
	return 0;
}

void 						add_new_range_memory(void *new_range_memory, size_t size, int _padding)
{
	t_range_memory 			*_new;
	t_range_memory 			*end;

	end = g_range_memory;
	if (!check_in_free_chunks(new_range_memory, size, _padding))
		{
			while (end && end->next)
				end = end->next;
			_new = (t_range_memory *)(new_range_memory + size);
			_new->address = new_range_memory;
			_new->size = size;
			_new->flag = 1;
			_new->padding = _padding;
			_new->next = NULL;
			_new->prev = end;
			end->next = _new;
		}
}

int 						alloc_mem_with_padding(void **new_range_memory, size_t size)
{
	int 					_padding;

	_padding = 0;
	while ((size + sizeof(t_range_memory) + _padding) % 8 != 0)
		_padding++;
	if ((*new_range_memory = sbrk(size + sizeof(t_range_memory) + _padding)) == (void *)-1)
	  {
	    perror("AAAAAAAAAAAAAAAAA");
	    return -1;
	  }
	return _padding;
}

void 						*my_malloc(size_t size)
{
	int 					_padding;
	size_t 					_size;
	void 					*new_range_memory;

	_padding = 0;
	new_range_memory = NULL;
	if (!size)
		return NULL;
	_size = align_size_4(size);
	if ((_padding = alloc_mem_with_padding(&new_range_memory, _size)) == -1)
		return NULL;
	if (!g_range_memory)
		{
			g_range_memory = (t_range_memory *)(new_range_memory + _size);
			g_range_memory->address = new_range_memory;
			g_range_memory->size = _size;
			g_range_memory->flag = 1;
			g_range_memory->padding = _padding;
			g_range_memory->prev = NULL;
			g_range_memory->next = NULL;
		}
	else
		add_new_range_memory(new_range_memory, _size, _padding);
	return (new_range_memory);
}
