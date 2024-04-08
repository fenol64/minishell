CC		:=	clang
NAME	:=	mini_api.a
CFLAGS	:=	-Wall -Wextra -ggdb3 -fsanitize=address -fsanitize=undefined -fsanitize=leak

INP_DIR		:=	input_handler/
INP_SRCS	:=	input_list_validation.c input_list_join.c input_split_expand.c \
						input_split_primary.c input_split_secondary.c input_split_utils.c input_structs.c

PROC_DIR	:=	proc_creator/
PROC_SRCS	:=	proc_creator_struct.c proc_creator_utils.c proc_filepaths.c proc_from_list.c \
						proc_get_path.c proc_hdoc_expand.c proc_open_files.c

BUILTINS_DIR	:=	builtins/
BUILTINS_SRCS	:=	builtins_envp.c builtins_utils.c builtins1.c builtins2.c

SRCS	:=	${addprefix $(INP_DIR), $(INP_SRCS)}
SRCS	+=	${addprefix $(PROC_DIR), $(PROC_SRCS)}
SRCS	+=	${addprefix $(BUILTINS_DIR), $(BUILTINS_SRCS)}

OBJS_DIR	:=	OBJS/
OBJS := ${SRCS:.c=.o}

OBJS_PREFIX	:= ${addprefix $(OBJS_DIR), $(OBJS)}

all:	$(NAME)

$(NAME):	$(OBJS_PREFIX)
	ar -rc $(NAME) $(OBJS_PREFIX)
	ranlib $(NAME)

$(OBJS_DIR)%.o:	%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	re fclean clean all