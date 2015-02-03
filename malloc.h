/*
** malloc.h for Malloc in /home/loxmi/Dropbox/Malloc/v2
**
** Made by THOMAS MILOX
** Login   <loxmi@epitech.net>
**
** Started on  Thu Jan 29 14:56:32 2015 THOMAS MILOX
** Last update Mon Feb  2 18:51:39 2015 THOMAS MILOX
*/

#ifndef __MALLOC_H__
# define __MALLOC_H__

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>

# define ALIGNMENT 				(4)
/*
** Structures
*/

typedef struct 					s_range_memory
{
	int							flag;
	int 						padding;
	void						*address;
	size_t						size;
	struct s_range_memory		*prev;
	struct s_range_memory 		*next;
}								t_range_memory;


typedef enum t_bool				t_bool;
enum t_bool
{
	FALSE,
	TRUE
};

/*
** Extern
*/

extern t_range_memory 		*g_range_memory;

/*
** Prototypes Fonctions
*/

/*				free.c 				*/
void 							my_free(void *);
t_bool 							check_chunks_flag(t_range_memory *);
void 							check_chunks_and_move_break();
void 							show_alloc_mem();
/* 				malloc.c 			*/
void 							*my_malloc(size_t);
size_t 							align_size_4(size_t);
void 							add_new_range_memory(void *, size_t);
int 							Scheck_in_free_chunks(void *, size_t);
#endif /* ! __MALLOC_H__ */
