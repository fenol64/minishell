NAME = minishell 

RAW_SRCS = $(shell find .)
SRCS = $(filter %.c, $(RAW_SRCS))
OBJS = $(SRCS:.c=.o)

COMPILER = cc -Wall -Wextra -Werror -I ./includes

.c.o:
	@ $(COMPILER) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
	@ $(COMPILER) -o $(NAME) $(OBJS)
	@ echo "✅ minishell compile complete!\n"

clean:
	@ rm -f $(OBJS)
	@ echo "🧹 minishell clean complete!\n"

fclean:	clean
	@rm -f $(NAME)
	@ echo "🧹 minishell fclean complete!\n"

re: clean fclean $(NAME)
	@ echo "🔄 minishell re complete!\n"
