/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:12:21 by fnascime          #+#    #+#             */
/*   Updated: 2024/04/26 14:34:04 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_includes/minishell.h"
#include "mini_includes/mini_typedefs.h"

static void	reset_main(t_main *main);
static bool empty_cmd(t_proc **procs);
static bool	empty_line(t_main *main);

int	main(int c, char **argv, char **envp)
{
	t_main	*main;

	setup_signals();
	main = new_main(envp);
	while (true)
	{
		main->inp_line = readline("Minishell$ ");
		if (!main->inp_line && !errno)
			break ;
		else if (!main->inp_line && errno)
			return (perror(__func__), free_main(main), EXIT_FAILURE);
		if (empty_line(main))
			continue ;
		add_history(main->inp_line);
		main->procs = get_procs(main);
		if (!main->procs)
			break ;
		if (!empty_cmd(main->procs))
			ft_pipeline(main);
		reset_main(main);
	}
	free_main(main);
	(void)c;
	(void)argv;
	return (EXIT_SUCCESS);
}

static void	reset_main(t_main *main)
{
	free(main->inp_line);
	free_proc_list(main->procs, free);
	lst_destroy2(main->input_list, free_token_node);
	main->procs = NULL;
	main->input_list = NULL;
	g_signal = 0;
	errno = 0;
	restore_fds(main);
}

static bool empty_cmd(t_proc **procs)
{
	size_t	index;

	index = 0;
	while (procs[index])
	{
		if (procs[index]->argv == NULL)
			return (true);
		index++;
	}
	return (false);
}

static bool	empty_line(t_main *main)
{
	char	*line;
	size_t	index;

	index = 0;
	line = main->inp_line;
	if (!line || !*line || g_signal == SIGINT)
	{
		free(line);
		g_signal = 0;
		main->inp_line = NULL;
		return (true);
	}
	while (line[index])
	{
		if (!ft_isspace(line[index]))
			return (false);
		index++;
	}
	free(line);
	main->inp_line = NULL;
	return (true);
}
