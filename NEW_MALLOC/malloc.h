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
# include "pthread.h"

# define ALIGNMENT 			(4)
# define HEADER_SIZE 		(sizeof(struct s_memory_chunk))
# define MAP_SIZE 			(21 * sysconf(_SC_PAGESIZE))

/*
** Structures
*/

typedef struct 				s_memory_chunk
{
	char 					_free;
	void 					*address;
	size_t 					size;
	uint32_t 				map_size;
	uint32_t 				magic_nbr;
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
extern t_memory_chunk 		*g_memory_map;
extern pthread_mutex_t 		mutex;

/*
** Prototypes fonctions
*/

void 						show_alloc_mem();
void 						*my_malloc(size_t);

#endif /* ! __MALLOC_H__ */

