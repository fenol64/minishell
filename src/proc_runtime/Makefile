deps	=	-L../libraries-dev
libs	=	-l:builtins.a -l:input_handler.a -l:proc_creator.a -l:structs.a  -lft_debug -llist_debug -lreadline

name	=	../libraries-dev/proc_runtime.a
SRCS	=	execute.c run_procs.c run_procs_utils.c

OBJS = ${SRCS:.c=.o}

all:	$(name)

$(name):	$(OBJS)
	ar -rcs $(name) $(OBJS)
	ranlib $(name)

exe:	$(OBJS)
	cc -Wall -Wextra -ggdb3 -o exe $(OBJS) main_test.c $(deps) $(libs)

%.o:	%.c
	cc -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all exe clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f exe $(name)

.PHONY: clean fclean all
