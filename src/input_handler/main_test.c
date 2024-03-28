#include "input_handler.h"

static void	p(void *arg);
static void free_node(void *arg);

int	main(int c, char **argv, char **envp)
{
	if (c != 2)
		return (printf("Invalid ARGC\n"), 1);
	
	t_list2	*list = input_split1(argv[1]);
	t_list2	*tlist = get_true_input(argv[1], envp);
	if (!validate_input_list(tlist))
		printf ("INVALID LIST !\n");
	char	*input = ft_strjoin_token_lst(tlist);
	printf("1st \n");
	lst_print2(list, p);
	printf("\n2nd \n");
	lst_print2(tlist, p);
	printf("\n");
	if (input)
		printf("%s\n", input);
	free(input);
	lst_destroy2(list, free_node);
	lst_destroy2(tlist, free_node);
	(void)c;
	(void)argv;
	(void)envp;
}

static void free_node(void *arg)
{
	t_token	*token = (t_token *)arg;
	free_token(token, free);
}

static void	p(void *arg)
{
	printf("value: (%s)\n", ((t_token *)arg)->value);
//	printf("type: %d\n", ((t_token *)arg)->type);
}