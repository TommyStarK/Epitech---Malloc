/*
** malloc.h for malloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:37 2015 THOMAS MILOX
** Last update Sun Feb  8 20:51:03 2015 Emmanuel Chambon
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
#	define ALIGNMENT 			(8)
# else
# 	define ALIGNMENT 			(4)
# endif

# define HEADER					(sizeof(struct s_memory_chunk))
# define ALIGN(size) 			(((size) + (ALIGNMENT - 1)) &~ (ALIGNMENT - 1))
# define MAP_SIZE 				ALIGN((ALIGNMENT * sysconf(_SC_PAGESIZE)))

/*
** Structures
*/

typedef enum t_bool 			t_bool;
enum t_bool
{
	FALSE,
	TRUE
};

typedef struct 					s_memory_chunk
{
  struct s_memory_chunk 		*prev;
  struct s_memory_chunk 		*next;
  struct s_memory_chunk 		*last;
  size_t						map_size;
  size_t						size;
  size_t 						a_size;
  void 							*address;
  t_bool	 					_free;
  t_bool 						a_free;
} 								t_memory_chunk;

/*
** Extern
*/
extern t_memory_chunk 			*g_memory_map;

/*
** Prototypes fonctions
*/

/*            malloc.c                  */
void 							*resize_memory_map(size_t);
void 							*split_memory_chunk(t_memory_chunk *, size_t);
void 							*set_new_chunk_memory(size_t);
void 							*add_new_chunk_memory(size_t);
void 							*init_memory_map(size_t);
void 							*malloc(size_t);
/*            free.c                    */
void 							show_alloc_mem();
void 							free(void *);

#endif /* ! __MALLOC_H__ */
