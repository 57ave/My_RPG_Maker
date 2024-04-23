##
## EPITECH PROJECT, 2023
## my_hunter
## File description:
## Makefile
##

NAME =	libmy.a

CC = gcc

CPPFLAGS += -iquote "../include"

CFLAGS = -Wall -Wextra -g3

SRC =	my_realloc.c 	\
		my_calloc.c 	\
		my_memcpy.c \
		my_strdup.c \
		my_strdup_delim.c 	\
		my_strlen.c \
		my_getnbr.c \
		my_strcmp.c \
		my_strncmp.c	\
		my_strcat.c \
		my_int_to_ascii.c 	\
		my_toml/open_toml.c \
		my_toml/get_objects.c 	\
		my_toml/get_data.c 	\
		my_toml/pull_data.c	\
		my_toml/pull_obj.c 	\
		vector/push_back_vector.c 	\
		vector/push_index_vector.c 	\
		vector/init_vector.c 	\

OBJ = 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc -o $(NAME) $(OBJ)
	cp libmy.a ../libmy.a

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

debug: CC = clang
debug: CFLAGS += -ggdb3
debug: fclean all

re: fclean all

.PHONY: all clean fclean re debug
