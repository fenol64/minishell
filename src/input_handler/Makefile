#deps	=	-l../libraries-dev/libft_debug.a -l../libraries-dev/liblist_debug.a
deps	=	-L../libraries-dev
libs	=	-l:structs.a -lft_debug -llist_debug
name	=	../libraries-dev/input_handler.a

SRCS =	input_split_primary.c input_split_utils.c input_split_secondary.c \
		input_split_expand.c input_list_validation.c input_list_join.c \
		input_signal_handler.c

OBJS = ${SRCS:.c=.o}

all:	$(name)

$(name):	$(OBJS)
		ar -rcs $(name) $(OBJS);
		ranlib $(name)

exe:	$(OBJS)
	cc -I../mini_typedefs -Wall -Wextra -ggdb3 -o exe $(OBJS) main_test.c $(deps) $(libs)

%.o:	%.c
	cc -I../mini_typedefs -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f exe $(name)

.PHONY: clean fclean all