##
## EPITECH PROJECT, 2024
## my_rpg
## File description:
## Makefile
##

NAME = my_rpg

NAME_TEST = unit_tests

LIB = libmy.a

LDFLAGS += -L.

LDLIBS = 	-lmy 	\
 			-lcsfml-graphics	\
			-lcsfml-window	\
			-lcsfml-system	\
			-lcsfml-audio

CFLAGS 	+= -Wall -Wextra

CPPFLAGS 	+= 	-iquote "include" 	\
			   	-iquote "include/ecs" 	\
				-iquote "include/ecs/component"

CC 	= gcc

SRC_TEST = 	tests/vector/init_test.c 	\
			tests/vector/push_back_test.c 	\
			tests/vector/push_index_test.c

SRC 	=

SRC_MAIN = 	src/main.c

OBJ_MAIN = $(SRC_MAIN:.c=.o)

OBJ = $(SRC:.c=.o)

OBJ_TEST = $(SRC_TEST:.c=.o)

all: $(OBJ)
	make -C lib
	$(CC) -o $(NAME) $(OBJ) $(OBJ_MAIN)

tests_run: 	LDLIBS += --coverage -lcriterion
tests_run:
	make -C lib
	$(CC) -o $(NAME_TEST) $(SRC) $(SRC_TEST) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
	./$(NAME_TEST)

clean:
	make -C lib clean
	$(RM) $(OBJ)
	$(RM) $(OBJ_MAIN)
	$(RM) *.gcno *.gcda
	$(RM) $(OBJ_TEST)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_TEST)
	make -C lib fclean
	$(RM) .save

asan: CC = clang
asan: LDFLAGS += -fsanitize=address
asan: re

debug:
	CFLAGS += -ggdb3
	all

re: fclean
re: all

.PHONY: all clean fclean debug asan re
