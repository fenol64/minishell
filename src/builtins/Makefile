SRCS =	builtins1.c builtins_envp.c builtins_envp_utils.c main_test.c 

OBJS = ${SRCS:.c=.o}

all:	exe

exe:	$(OBJS)
	cc -Wall -Wextra -ggdb3 -o exe $(OBJS) exe.a proc.a liblist_debug.a libft_debug.a -lreadline

%.o:	%.c
	cc -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f exe

.PHONY: clean fclean all