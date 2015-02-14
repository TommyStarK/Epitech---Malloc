/*
** malloc.h for malloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:37 2015 THOMAS MILOX
** Last update Wed Feb 11 20:38:15 2015 THOMAS MILOX
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

# ifndef __X86_64__
#	define ALIGNMENT 	       	(16)
# else
# 	define ALIGNMENT       		(8)
# endif

# define HEADER				(sizeof(struct s_memory_chunk))
# define ALIGN(size) 			(((size) + (ALIGNMENT - 1)) &~ (ALIGNMENT - 1))
# define MAP_SIZE 			ALIGN((ALIGNMENT * sysconf(_SC_PAGESIZE)))

/*
** Structures
*/

typedef enum t_bool 			t_bool;
enum t_bool
{
	FALSE,
	TRUE
};

typedef struct 				s_memory_chunk
{
  struct s_memory_chunk 		*prev;
  struct s_memory_chunk 		*next;
  struct s_memory_chunk 		*last;
  struct s_memory_chunk 		*next_freed;
  struct s_memory_chunk 		*prev_freed;
  struct s_memory_chunk 		*last_freed;
  size_t				map_size;
  size_t				size;
  size_t 				a_size;
  size_t				n_size;
  void 					*address;
  t_bool	 			_free;
} 				      	t_memory_chunk;

/*
** Extern
*/
extern t_memory_chunk 			*g_memory_map;
extern t_memory_chunk 			*g_memory_freed;

/*
** Prototypes fonctions
*/

/*            malloc.c                  */
void 					*resize_memory_map(size_t);
void 					*split_memory_chunk(t_memory_chunk **, size_t);
void 					*set_new_chunk_memory(size_t);
void 					*add_new_chunk_memory(size_t);
void 					*init_memory_map(size_t);
void 					*malloc(size_t);
/*            free.c                    */
void 					show_alloc_mem();
void 					bring_back_break();
void 					free(void *);

#endif /* ! __MALLOC_H__ */
