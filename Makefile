##
## Makefile for Makefile in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
## 
## Made by THOMAS MILOX
## Login   <loxmi@epitech.net>
## 
## Started on  Sat Feb  7 21:38:39 2015 THOMAS MILOX
## Last update Sun Feb 15 00:04:10 2015 THOMAS MILOX
##

CC	=	gcc

RM	=	rm -f

NAME	=	libmy_malloc_$(HOSTTYPE).so

CFLAGS	=	-Wall -Wextra -fPIC

SRC	=	malloc.c		\
		malloc_handler.c	\
		realloc.c		\
		calloc.c		\
		tools.c			\
		free.c 		

OBJ	=	$(SRC:.c=.o)

$(NAME)	:	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -shared -o $(NAME)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
