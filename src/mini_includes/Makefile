name	=	../libraries-dev/structs.a

SRCS =	free_structs.c free_struc_node.c main_structs.c

OBJS = ${SRCS:.c=.o}

all:	$(name)

$(name):	$(OBJS)
	ar -rcs $(name) $(OBJS);
	ranlib $(name)

%.o:	%.c
	cc -Wall -Wextra -ggdb3 -c $< -o $@

mclean: all clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(name)

.PHONY: clean fclean all