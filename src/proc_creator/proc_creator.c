/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:14:43 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/17 09:41:28 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static void	get_cmd_paths(t_proc **procs, t_main *main);
static void	init_here_docs(t_proc **procs, t_main *main);
static void	open_redirect_files(t_proc **procs);

t_proc	**get_procs(t_list2 *list, t_main *main)
{;
	if (!list || !main)
		return (ft_perror(__func__, ARGNULL), NULL);
	main->init_status = 1;
	main->procs = init_procs(list, main);
	main->init_status = 0;
	if (!main->procs)
		return (NULL);
	init_here_docs(main->procs, main);
	main->init_status = 1;
	open_redirect_files(main->procs);
	get_cmd_paths(main->procs, main);
	main->init_status = 0;
	return (main->procs);
}

void	init_here_docs(t_proc **procs, t_main *main)
{
	t_file	*file;
	size_t	index;
	t_list2	*tmp;

	index = 0;
	while (procs[index])
	{
		tmp = procs[index]->infiles;
		while (tmp)
		{
			file = (t_file *)tmp->data;
			if (file->mode == -42)
			{
				if (!get_here_doc(file, main))
				{
					free_main(main);
					exit(EXIT_FAILURE);
				}
			}
			tmp = tmp->next;
		}
		index++;
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
		if (!get_path(procs[index], main))
		{
			free_main(main);
			exit(EXIT_FAILURE);
		}
		index++;
	}
}