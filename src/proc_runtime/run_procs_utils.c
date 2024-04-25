/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_procs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:27:40 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/25 13:33:16 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_runtime.h"

size_t	proc_len(t_main *main)
{
	size_t	size;

	size = 0;
	while (main->procs[size])
		size++;
	return (size);
}

void	close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	write_hdoc(t_file *file, int fd)
{
	if (write(fd, file->name, ft_strlen(file->name)) == -1)
		perror(__func__);
}

t_file	*get_inputfile(t_proc *proc)
{
	t_file	*file;
	t_list2	*tmp;

	if (!proc->infiles)
		return (NULL);
	tmp = proc->infiles;
	tmp = last_node2(tmp);
	if (is_builtin(proc->argv->data))
	{
		file = (t_file *)tmp->data;
		while (tmp && file->mode == -42)
		{
			file = (t_file *)tmp->data;
			tmp = tmp->prev;
		}
	}
	return ((t_file *)tmp->data);
}

t_file	*get_outputfile(t_proc *proc)
{
	t_file	*file;
	t_list2	*tmp;

	if (!proc->outfiles)
		return (NULL);
	tmp = proc->outfiles;
	tmp = last_node2(tmp);
	return ((t_file *)tmp->data);
}