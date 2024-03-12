NAME = minishell 

RAW_SRCS = $(shell find src)
SRCS = $(filter %.c, $(RAW_SRCS))
OBJS = $(SRCS:.c=.o)

COMPILER = cc -Wall -Wextra -Werror -I ./includes
LIBS_ARCHIVE = libs/libft/libft.a

.c.o:
	@ $(COMPILER) -c $< -o $(<:.c=.o)
	@printf "🚧 minishell compiling $<                       \r"

all: $(NAME)

libs:
	@ make -C libs/libft

$(NAME):	$(OBJS)
	@ $(COMPILER) -o $(NAME) $(OBJS) $(LIBS_ARCHIVE) -lreadline
	@ printf "\n🚀 minishell compile complete!\n"

clean:
	@ make -C libs/libft clean
	@ rm -f $(OBJS)
	@ printf "🧹 minishell clean complete!\n"

fclean:	clean
	@ make -C libs/libft fclean
	@rm -f $(NAME)
	@ printf "🧹 minishell fclean complete!\n"

re: clean fclean $(NAME)
	@ printf "🔄 minishell re complete!\n"
