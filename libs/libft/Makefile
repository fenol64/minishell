NAME = libft.a
DEBUG_NAME = libft_debug.a

RAW_SRCS= $(shell find .)
SRCS = $(filter %.c, $(RAW_SRCS))
OBJS = $(SRCS:.c=.o)
DEBUG_OBJS = ${OBJS:.o=_debug.o}

COMPILER = cc -Wall -Wextra -Werror -I ./includes

.c.o:
	@ $(COMPILER) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
	@ ar rc $(NAME) $(OBJS)
	@ echo "✅ libft compile complete!\n"

debug: $(DEBUG_NAME)

$(DEBUG_NAME):	$(DEBUG_OBJS)
	@ ar rc $(DEBUG_NAME) $(DEBUG_OBJS)
	@ echo "✅ libft debug compile complete!\n"

%_debug.o:	%.c
	@ $(COMPILER) -ggdb3 -c $< -o $@

clean:
	@ rm -f $(OBJS) $(DEBUG_OBJS)
	@ echo "🧹 libft clean complete!\n"

fclean:	clean
	@rm -f $(NAME) $(DEBUG_NAME)
	@ echo "🧹 libft fclean complete!\n"

re: clean fclean $(NAME)
	@ echo "🔄 libft re complete!\n"


