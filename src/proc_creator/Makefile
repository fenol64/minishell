deps	=	-L../libraries-dev
libs	=	-l:input_handler.a -l:structs.a -lft_debug -llist_debug -lreadline
name	=	../libraries-dev/proc_creator.a

SRCS =	proc_creator_utils.c proc_from_list.c proc_hdoc_expand.c proc_open_files.c \
		proc_filepaths.c proc_get_path.c proc_creator.c

OBJS = ${SRCS:.c=.o}

all:	$(name)

$(name):	$(OBJS)
	ar -rcs $(name) $(OBJS);
	ranlib $(name)

exe:	$(OBJS)
	cc -Wall -Wextra -ggdb3 -o exe $(OBJS) main_test.c $(deps) $(libs)

%.o:	%.c
	cc -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f  exe $(name)

.PHONY: clean fclean all