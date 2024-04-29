/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:12:21 by fnascime          #+#    #+#             */
/*   Updated: 2024/04/29 14:33:33 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mini_typedefs.h"

static void	reset_main(t_main *main);
static bool	empty_cmd(t_proc **procs);
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
		else if (!main->inp_line && errno && errno != ENOTTY)
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
	if (g_signal == SIGCHLD && !ft_strcmp(main->exit_status, "130"))
		write(STDOUT_FILENO, "\n", 1);
	free(main->inp_line);
	free_proc_list(main->procs, free);
	lst_destroy2(main->input_list, free_token_node);
	main->procs = NULL;
	main->input_list = NULL;
	g_signal = 0;
	errno = 0;
	restore_fds(main);
}

static bool	empty_cmd(t_proc **procs)
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
	char		*line;
	size_t		index;
	static int	last_signal = 0;

	index = 0;
	line = main->inp_line;
	if (!line || !*line || g_signal == SIGINT)
	{
		main->inp_line = NULL;
		if ((g_signal == SIGINT && last_signal == 0))
			write(STDERR_FILENO, "\n", 1);
		last_signal = g_signal;
		g_signal = 0;
		return (restore_fds(main), free(line), rl_on_new_line(), true);
	}
	last_signal = 0;
	while (line[index])
	{
		if (!ft_isspace(line[index]))
			return (false);
		index++;
	}
	free(line);
	main->inp_line = NULL;
	return (rl_on_new_line(), true);
}
