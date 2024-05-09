CC		:=	clang
NAME	:=	minishell
CFLAGS	:=	-Wall -Wextra -ggdb3
LIBS	:=	-L./libraries-dev -lft_debug -llist_debug -lreadline

COMMON_DIR	:=	mini_includes/
COMMON_SRCS	:=	free_struct_node.c free_structs.c main_structs.c structs_utils.c main.c \

INP_DIR		:=	input_handler/
INP_SRCS	:=	input_list_validation.c input_list_join.c input_split_expand.c \
				input_split_primary.c input_split_secondary.c input_split_utils.c \
				input_signal_handler.c input_split_secondary_helper.c \

PROC_DIR	:=	proc_creator/
PROC_SRCS	:=	proc_filepaths.c proc_from_list.c proc_heredoc.c \
				proc_get_path.c proc_hdoc_expand.c proc_open_files.c proc_creator.c \

BUILTINS_DIR	:=	builtins/
BUILTINS_SRCS	:=	builtins_envp.c builtins_utils.c builtins1.c builtin_export.c builtin_unset.c \

PROC_RUN_DIR	:=	proc_runtime/
PROC_RUN_SRCS	:=	execute.c run_procs_utils.c run_procs.c \

SRCS	:=	${addprefix $(COMMON_DIR), $(COMMON_SRCS)}
SRCS	+=	${addprefix $(INP_DIR), $(INP_SRCS)}
SRCS	+=	${addprefix $(PROC_DIR), $(PROC_SRCS)}
SRCS	+=	${addprefix $(BUILTINS_DIR), $(BUILTINS_SRCS)}
SRCS	+=	${addprefix $(PROC_RUN_DIR), $(PROC_RUN_SRCS)}

OBJS_DIR	:=	OBJS/
OBJS := ${SRCS:.c=.o}

OBJS_PREFIX	:= ${addprefix $(OBJS_DIR), $(OBJS)}

all:	$(NAME)

$(NAME):	$(OBJS_PREFIX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_PREFIX) $(LIBS)

$(OBJS_DIR)%.o:	%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean:	clean
	rm -rf $(NAME)

mclean: fclean all

re:	fclean all

.PHONY:	re fclean clean all