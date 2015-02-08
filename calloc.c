/*
** calloc.c for calloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:07 2015 THOMAS MILOX
** Last update Thu Feb  5 14:41:10 2015 THOMAS MILOX
*/

#include "malloc.h"

void			*calloc(size_t nmemb, size_t size)
{
	void		*mem;
  	size_t		total;

	total = nmemb * size;
	if (size && (total / size != nmemb))
	{
	   errno = ENOMEM;
	   return (NULL);
	}
	if ((mem = malloc(total)) == NULL)
	{
	   errno = ENOMEM;
	   return (NULL);
	}
	return (memset(mem, 0, total));
}