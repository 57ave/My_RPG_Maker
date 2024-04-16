##
## EPITECH PROJECT, 2024
## my_rpg
## File description:
## Makefile
##

NAME = my_rpg

LIB = libmy.a

LDFLAGS += -L.

LDLIBS = 	-lmy 	\
 			-lcsfml-graphics	\
			-lcsfml-window	\
			-lcsfml-system	\
			-lcsfml-audio

CFLAGS += -Wall -Wextra

CPPFLAGS += -iquote "include"

CC = gcc

SRC = 	src/main.c	\

OBJ = $(SRC:.c=.o)

all: $(OBJ)
	make -C lib
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	make -C lib fclean
	$(RM) .save

debug: CC = clang
debug: CFLAGS += -ggdb3 -fsanitize=address -g
debug: $(OBJ)
	make -C lib/ debug
	$(CC) -o $(NAME) $(OBJ) -fsanitize=address

re: fclean
re: all

.PHONY: all clean fclean debug re
