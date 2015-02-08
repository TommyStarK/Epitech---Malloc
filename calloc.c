/*
** calloc.c for calloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:07 2015 THOMAS MILOX
** Last update Sun Feb  8 19:04:15 2015 Emmanuel Chambon
*/

#include "malloc.h"

void			*calloc(size_t nbr_alloc, size_t size)
{
  void			*chunk;
  size_t		total;

  total = nbr_alloc * size;
  if (size && (total / size != nbr_alloc))
    {
      errno = ENOMEM;
      return (NULL);
    }
  if ((chunk = malloc(total)) == NULL)
    {
      errno = ENOMEM;
      return (NULL);
    }
  return (memset(chunk, 0, total));
}
