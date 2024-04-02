/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_creator_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:03:00 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/02 11:02:31 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

t_file	*new_file(void)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (perror(__func__), NULL);
	file->fd = -1;
	file->mode = 0;
	file->name = NULL;
	return (file);
}

t_proc	*new_proc(void)
{
	t_proc	*proc;

	proc = malloc(sizeof(t_proc));
	if (!proc)
		return (perror(__func__), NULL);
	proc->argv = NULL;
	proc->envp = NULL;
	proc->infiles = NULL;
	proc->outfiles = NULL;
	proc->pfd[0] = -1;
	proc->pfd[1] = -1;
	return (proc);
}

void	free_file(t_file *file, void (*del)(void *arg))
{
	if (!file)
		return ;
	if (del)
		del(file->name);
	free(file);
}

void	free_proc(t_proc *proc, void (*del_arg)(void *a))
{
	if (!proc)
		return ;
	close_proc_files(proc);
	lst_destroy2(proc->argv, del_arg);
	free(proc);
}

void	free_proc_list(t_proc **procs, void (*del)(void *arg))
{
	size_t	index;

	index = 0;
	if (!procs)
		return ;
	while (procs[index])
	{
		free_proc(procs[index]);
		index++;
	}
	free(procs);
}
