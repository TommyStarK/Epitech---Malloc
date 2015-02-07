/*
** free.c for Free in /home/loxmi/Dropbox/Malloc/v2
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Jan 29 14:56:16 2015 THOMAS MILOX
** Last update Sat Feb  7 01:47:10 2015 THOMAS MILOX
*/

#include "malloc.h"

/*
** Show_alloc_mem()
*/

void 						show_alloc_mem()
{
  size_t 					max_size;
  t_range_memory 			*tmp;

  max_size = 0;
  tmp = g_range_memory;
  while (tmp)
    {
      max_size += tmp->size;
      tmp = tmp->next;
    }
  printf("break : %p\n", ((t_range_memory *)(g_range_memory + max_size)));
  tmp = g_range_memory;
  while (tmp)
    {
      printf("%p - %p : %lu octets\n", tmp->address,
	     ((t_range_memory *)(tmp->address + tmp->size)), tmp->size);
      tmp = tmp->next;
    }
}

/*
** Fonctions pour Free
*/

t_bool 				check_chunks_flag(t_range_memory *chunk)
{
  t_range_memory 	*tmp;

  tmp = chunk;
  while (tmp)
    {
      if (tmp->flag == 1)
	return FALSE;
      tmp = tmp->next;
    }
  return TRUE;
}

void 				check_chunks_and_move_break()
{
  t_range_memory 	*tmp;

  tmp = g_range_memory;
  while (tmp && tmp->flag)
    tmp = tmp->next;
  if (check_chunks_flag(tmp) == TRUE)
    {
      t_range_memory *bckp;
      t_range_memory *clean;
      bckp = tmp;
      while (tmp)
	{
	  clean = tmp;
	  tmp->flag = 0;
	  bzero((void *)(tmp->address + tmp->size), STRUCT_SIZE);
	  tmp = tmp->next;
	  clean->prev = NULL;
	  clean->next = NULL;
	}
      if (brk(bckp) == -1)
	return;
    }
}

void 				my_free(void *ptr)
{
  if (!ptr || !g_range_memory)
    return;
  if (!g_range_memory->next)
    {
      bzero(g_range_memory->address, g_range_memory->size);
      bzero((void *)(g_range_memory->address + g_range_memory->size),
	    STRUCT_SIZE);
      if (brk(g_range_memory->address) == -1)
	return;
      g_range_memory = NULL;
      ptr = NULL;
    }
  else
    {
      t_range_memory 	*tmp;
      tmp = g_range_memory;
      while (tmp && tmp->address != ptr)
	tmp = tmp->next;
      bzero(tmp->address, tmp->size);
      tmp->flag = 0;
      ptr = NULL;
      check_chunks_and_move_break();
    }
}
