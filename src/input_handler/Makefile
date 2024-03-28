SRCS =	input_split_primary.c input_split_utils.c input_structs.c \
		input_split_secondary.c input_split_expand.c input_list_validation.c input_list_join.c

OBJS = ${SRCS:.c=.o}

all:	exe.a

exe.a:	$(OBJS)
	ar -rc exe.a $(OBJS);
	ranlib exe.a

#exe:	$(OBJS)
#	cc -I./stuff -Wall -Wextra -ggdb3 -o exe $(OBJS) stuff/liblist_debug.a stuff/libft_debug.a

%.o:	%.c
	cc -I./stuff -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f exe input.a

.PHONY: clean fclean all