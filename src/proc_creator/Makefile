SRCS =	proc_creator_struct.c proc_creator_utils.c proc_from_list.c proc_hdoc_expand.c proc_open_files.c \
		proc_filepaths.c proc_get_path.c main_test.c 

OBJS = ${SRCS:.c=.o}

all:	exe

exe:	$(OBJS)
	cc -Wall -Wextra -ggdb3 -o exe $(OBJS) exe.a libft_debug.a liblist_debug.a -lreadline

%.o:	%.c
	cc -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f exe 

.PHONY: clean fclean all