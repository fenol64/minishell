deps	=	-L../libraries-dev
libs	=	-l:input_handler.a -l:proc_creator.a -l:structs.a -l:builtins.a -lft_debug -llist_debug -lreadline

name	=	../libraries-dev/proc_runtime.a
SRCS	=	execute.c

OBJS = ${SRCS:.c=.o}

all:	$(name)

$(name):	$(OBJS)
	ar -rcs $(name) $(OBJS)
	ranlib $(name)

exe:	$(OBJS)
	clang -Wall -Wextra -ggdb3 -o exe $(OBJS) main_test.c $(deps) $(libs)

%.o:	%.c
	clang -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all exe clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f exe $(name)

.PHONY: clean fclean all
