/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:14:43 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/26 13:52:45 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static void	get_cmd_paths(t_proc **procs, t_main *main);
static void	init_here_docs(t_proc **procs, t_main *main);
static void	open_redirect_files(t_proc **procs);

t_proc	**get_procs(t_main *main)
{
	if (!main || !main->inp_line)
		return (ft_perror(__func__, ARGNULL), NULL);
	main->input_list = get_true_input(main->inp_line, main);
	if (!main->input_list)
		return (NULL);
	main->procs = init_procs(main->input_list, main);
	if (!main->procs)
		return (NULL);
	init_here_docs(main->procs, main);
	open_redirect_files(main->procs);
	get_cmd_paths(main->procs, main);
	return (main->procs);
}

void	init_here_docs(t_proc **procs, t_main *main)
{
	int		index;
	t_list2	*tmp;

	index = -1;
	while (procs[++index])
	{
		tmp = procs[index]->infiles;
		while (tmp)
		{
			if (((t_file *)tmp->data)->mode == -42)
			{
				if (!get_here_doc((t_file *)tmp->data, main))
				{
					if (g_signal == SIGINT)
						restore_fds(main);
					if (errno)
					{
						free_main(main);
						exit(EXIT_FAILURE);
					}
				}
			}
			tmp = tmp->next;
		}
	}
}

static void	open_redirect_files(t_proc **procs)
{
	size_t	index;

	index = 0;
	while (procs[index])
	{
		open_proc_infiles(procs[index]);
		open_proc_outfiles(procs[index]);
		index++;
	}
}

static void	get_cmd_paths(t_proc **procs, t_main *main)
{
	size_t	index;

	index = 0;
	while (procs[index])
	{
		if (!get_path(procs[index], main) && errno)
		{
			free_main(main);
			exit(EXIT_FAILURE);
		}
		index++;
	}
}