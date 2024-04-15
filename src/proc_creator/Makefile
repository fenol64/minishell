deps	=	-l../libraries-dev/libft_debug.a -l../libraries-dev/liblist_debug.a -l../libraries-dev/input_handler.a
name	=	../libraries-dev/proc_creator.a

SRCS =	proc_creator_utils.c proc_from_list.c proc_hdoc_expand.c proc_open_files.c \
		proc_filepaths.c proc_get_path.c

OBJS = ${SRCS:.c=.o}

all:	$(name)

#exe:	$(OBJS)
#	cc -Wall -Wextra -ggdb3 -o exe $(OBJS) exe.a libft_debug.a liblist_debug.a -lreadline

$(name):	$(OBJS)
	ar -rc $(name) $(OBJS);
	ranlib $(name)

exe:	proc.a
	cc -Wall -Wextra -ggdb3 -o exe $(OBJS) main_test.c $(deps)

%.o:	%.c
	cc -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f  exe $(name)

.PHONY: clean fclean all