SRCS =	proc_creator_struct.c proc_creator_utils.c proc_from_list.c proc_hdoc_expand.c proc_open_files.c \
		proc_filepaths.c proc_get_path.c

OBJS = ${SRCS:.c=.o}

all:	proc.a

#exe:	$(OBJS)
#	cc -Wall -Wextra -ggdb3 -o exe $(OBJS) exe.a libft_debug.a liblist_debug.a -lreadline

proc.a:	$(OBJS)
	ar -rc proc.a $(OBJS);
	ranlib proc.a

exe:	proc.a
	cc -Wall -Wextra -ggdb3 -o exe $(OBJS) main_test.c exe.a proc.a libft_debug.a liblist_debug.a -lreadline

%.o:	%.c
	cc -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f  proc.a

.PHONY: clean fclean all