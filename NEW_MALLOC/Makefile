##
## Makefile for Makefile in /home/loxmi/Dropbox/Malloc/v2/PSU_2014_malloc/NEW_MALLOC
## 
## Made by THOMAS MILOX
## Login   <loxmi@epitech.net>
## 
## Started on  Sat Feb  7 21:38:39 2015 THOMAS MILOX
## Last update Sat Feb  7 21:42:49 2015 THOMAS MILOX
##

SRC = 		malloc.c \
		malloc_handler.c \
		realloc.c 	\
		calloc.c 	\
		free.c 		

OBJ = 		$(SRC:.c=.o)

NAME = 		libmy.so

regle:		
		gcc -c -fpic $(SRC)


$(NAME):	regle
		gcc -shared -o $(NAME) $(OBJ)