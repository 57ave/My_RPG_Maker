##
## EPITECH PROJECT, 2024
## my_rpg
## File description:
## Makefile
##

NAME = my_rpg

NAME_TEST = unit_tests

LIB = libmy.a

LDFLAGS += -L./lib

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

SRC 	=	src/launch_rpg.c \
			src/lauching_error_handling.c \
			src/ecs/init_type.c 	\
			src/ecs/components/init_component.c	\
			src/ecs/components/init_drawable.c	\
			src/ecs/components/init_game_mode.c	\
			src/ecs/components/init_health.c	\
			src/ecs/components/init_position.c	\
			src/ecs/components/init_velocity.c	\
			src/ecs/components/init_temporary.c	\
			src/ecs/components/init_text.c	\
			src/ecs/components/init_damage.c	\
			src/ecs/isolate_entities.c	\
			src/ecs/systems/drawing_system.c	\
			src/ecs/read_config.c

SRC_MAIN = 	src/main.c

OBJ_MAIN = $(SRC_MAIN:.c=.o)

OBJ = $(SRC:.c=.o)

OBJ_TEST = $(SRC_TEST:.c=.o)

all: $(OBJ_MAIN) $(OBJ)
	make -C lib
	$(CC) -o $(NAME) $(OBJ_MAIN) $(OBJ) $(LDFLAGS) $(LDLIBS)

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
asan: LDFLAGS += -fsanitize=address -static-libsan
asan: re

debug: CFLAGS += -ggdb
debug: re

warning: CFLAGS += -Werror
warning: re

re: fclean
re: all

.PHONY: all clean fclean debug asan warning re
