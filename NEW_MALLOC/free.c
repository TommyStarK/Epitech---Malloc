/*
** free.c for free in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:24 2015 THOMAS MILOX
** Last update Thu Feb  5 14:41:25 2015 THOMAS MILOX
*/

#include "malloc.h"

void                        show_alloc_mem()
{
  t_memory_chunk          *tmp;

  tmp = g_memory_map;
  	if (!tmp)
  		return;
  printf("break : %p\n", g_memory_map->_break);
  while (tmp)
    {
      printf("header [%p] address data :[%p] end_data : [%p] = %lu octets  magic_nbr %li\n"
      	, tmp, tmp->address, ((void *)tmp->address + tmp->size),tmp->size, tmp->magic_nbr);
      tmp = tmp->next;
    }
}

