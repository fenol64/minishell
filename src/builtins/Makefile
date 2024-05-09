deps	=	-L../libraries-dev
libs	=	-l:proc_creator.a -l:input_handler.a -l:structs.a -lft_debug -llist_debug -lreadline

name	=	../libraries-dev/builtins.a
SRCS	=	builtins1.c builtins_envp.c builtins_utils.c builtin_export.c builtin_unset.c

OBJS = ${SRCS:.c=.o}

all:	$(name)

$(name):	$(OBJS)
	ar -rcs $(name) $(OBJS)
	ranlib $(name)

exe:	$(OBJS)
	cc -Wall -Wextra -ggdb3 -o exe $(OBJS) main_test.c $(deps) $(libs)

%.o:	%.c
	cc -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f exe $(name)

.PHONY: clean fclean all