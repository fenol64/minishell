SRCS =	input_split_primary.c input_split_utils.c main_test.c input_structs.c \
		input_split_secondary.c input_split_expand.c

OBJS = ${SRCS:.c=.o}

all:	exe

exe:	$(OBJS)
	cc -I./stuff -Wall -Wextra -ggdb3 -o exe $(OBJS) stuff/liblist_debug.a stuff/libft_debug.a

%.o:	%.c
	cc -I./stuff -Wall -Wextra -ggdb3 -c $< -o $@ 

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f exe

.PHONY: clean fclean all