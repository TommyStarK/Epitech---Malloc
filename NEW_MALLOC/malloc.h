/*
** malloc.h for malloc in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Feb  5 14:41:37 2015 THOMAS MILOX
** Last update Thu Feb  5 14:42:07 2015 THOMAS MILOX
*/

#ifndef __MALLOC_H__
# define __MALLOC_H__

# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "string.h"
# include "stdint.h"
# include "signal.h"
# include "pthread.h"

# define ALIGNMENT 			(8)
# define ALIGN_SIZE(size) 	(((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
# define HEADER_SIZE 		(sizeof(struct s_memory_chunk))
# define MAP_SIZE 			(21 * sysconf(_SC_PAGESIZE))

/*
** Structures
*/

typedef struct 				s_memory_chunk
{
	char 					_free;
	void 					*address;
	void 					*_break;
	size_t 					size;
	uint64_t 				map_size;
	uint64_t 				magic_nbr;
	struct s_memory_chunk 	*next;
	struct s_memory_chunk 	*prev;
} 							t_memory_chunk;


typedef enum t_bool 		t_bool;
enum t_bool
{
	FALSE,
	TRUE
};

/*
** Extern
*/
extern int 					g_free;
extern t_memory_chunk 		*g_memory_map;
extern pthread_mutex_t 		mutex;

/*
** Prototypes fonctions
*/

/*            malloc.c                  */
size_t 						resize_memory_handler();
void 						*set_new_chunk_memory_handler(size_t size);
void 						*resize_memory_map(size_t);
void 						*split_memory_chunk(t_memory_chunk *, size_t);
void 						*set_new_chunk_memory(size_t);
void 						*add_new_chunk_memory(size_t);
void 						*init_memory_map(size_t);
void 						*my_malloc(size_t);
/*            free.c                    */
void 						show_alloc_mem();
void 						my_free(void *);

#endif /* ! __MALLOC_H__ */
