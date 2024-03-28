#include "proc_creator.h"

static void	p(void *arg);
static void free_node(void *arg);
static void	print_proc(t_proc *proc);

int	main(int c, char **argv, char **envp)
{
	if (c != 2)
		return (printf("Invalid ARGC\n"), 1);
	t_proc	**procs;	
	t_list2	*tlist = get_true_input(argv[1], envp);
	if (!validate_input_list(tlist))
		printf ("INVALID LIST !\n");
	procs = get_procs(tlist, envp);
	if (!procs)
		printf("OOPS, PRoc faileD!\n");

	print_proc(*procs);

	free_proc_list(procs, free);
	lst_destroy2(tlist, free_token_node);
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
	printf("type: %d\n", ((t_token *)arg)->type);
}

static void	p3(void *arg)
{
	printf("%s ", (char *)arg);
}

static void	p2(void *arg)
{
	printf("fd: %d\n", ((t_file *)arg)->fd);
	printf("name: (%s)\n", ((t_file *)arg)->name);
	printf("mode: (%d)\n", ((t_file *)arg)->mode);
	printf("\n");
}

static void	print_proc(t_proc *proc)
{
	if (!proc)
		printf("proc is NULL");
	printf("pfd: [%d][%d]\n", proc->pfd[0], proc->pfd[1]);
	printf ("ARGUMENTS: ");
	lst_print2(proc->argv, p3);
	printf("\n\n");
	printf ("infiles: \n");
	lst_print2(proc->infiles, p2);
	printf("\n\n");
	printf ("outfiles: ");
	lst_print2(proc->outfiles, p2);
	printf("\n\n");
}