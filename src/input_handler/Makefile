deps	=	-l../libraries-dev/libft_debug.a -l../libraries-dev/liblist_debug.a
name	=	../libraries-dev/input_handler.a

SRCS =	input_split_primary.c input_split_utils.c input_split_secondary.c \
		input_split_expand.c input_list_validation.c input_list_join.c

OBJS = ${SRCS:.c=.o}

all:	$(name)

$(name):	$(OBJS)
		ar -rcs $(name) $(OBJS);
		ranlib $(name)

exe:	$(OBJS)
	cc -I../mini_typedefs -Wall -Wextra -ggdb3 -o exe $(OBJS) $(deps)

%.o:	%.c
	cc -I../mini_typedefs -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f exe $(name)

.PHONY: clean fclean all