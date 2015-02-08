/*
** show_mem.c for  in /home/chambo_e/epitech/PSU_2014_malloc/malloc_manu
**
** Made by Emmanuel Chambon
** Login   <chambo_e@epitech.net>
**
** Started on  Sun Feb  8 15:54:54 2015 Emmanuel Chambon
** Last update Sun Feb  8 16:58:47 2015 Emmanuel Chambon
*/

#include "malloc.h"

void			show_alloc_mem()
{
  //  size_t		data;
  t_memory_chunk	*tmp;

  tmp = g_memory_map;
  printf("break : 0x%lX\n", (size_t) sbrk(0));
  while (tmp)
    {
      //      data = (size_t)tmp + HEADER;
        /*     if (!tmp->free) */
	/* printf("0x%lX - 0x%lX : %lu bytes\n", */
	/*        data, data + tmp->size, tmp->size); */
      tmp = tmp->next;
    }
}
