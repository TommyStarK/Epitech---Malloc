/*
** malloc.h for malloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:37 2015 THOMAS MILOX
** Last update Sun Feb  8 17:27:17 2015 Emmanuel Chambon
*/

#ifndef __MALLOC_H__
# define __MALLOC_H__

# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <signal.h>
# include <pthread.h>

# ifndef _X86_64__
#	define ALIGNMENT		(8)
# else
# 	define ALIGNMENT		(4)
# endif

# define HEADER				(sizeof(struct s_memory_chunk))
# define ALIGN(size)			(((size) + (ALIGNMENT - 1)) &~ (ALIGNMENT - 1))
# define MAP_SIZE			ALIGN(((3 * ALIGNMENT) * sysconf(_SC_PAGESIZE)))

/*
** Structures
*/
typedef struct				s_memory_chunk
{
  struct s_memory_chunk			*prev;
  struct s_memory_chunk			*next;
  struct s_memory_chunk			*last;
  size_t				csize;
  size_t				msize;
  void					*chunk;
  char					free;
}					t_memory_chunk;

/*
** Extern
*/
extern t_memory_chunk			*g_memory_map;

/*
** Prototypes fonctions
*/

void 						*malloc(size_t);

void 						free(void *);

void 						show_alloc_mem();

void						*realloc(void *, size_t);

#endif /* ! __MALLOC_H__ */
