/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_open_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:14:50 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/02 15:34:45 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static int	infile_exit(t_proc *proc);
static int	outfile_exit(t_proc *proc);

int	close_proc_files(t_proc *proc)
{
	t_file	*file;
	t_list2	*tmp;
	t_list2	*tmp2;

	tmp = proc->infiles;
	while (tmp)
	{
		file = (t_file *)tmp->data;
		if (file->mode != -42 && file->fd != -1)
			close(file->fd);
		tmp = tmp->next;
	}
	tmp2 = proc->outfiles;
	while (tmp2)
	{
		file = (t_file *)tmp2->data;
		if (file->fd != -1)
			close(file->fd);
		tmp2 = tmp2->next;
	}
	lst_destroy2(proc->infiles, del_file_node);
	lst_destroy2(proc->outfiles, del_file_node);
	proc->infiles = NULL;
	proc->outfiles = NULL;
	return (true);
}

int	open_proc_outfiles(t_proc *proc)
{
	t_file	*file;
	t_list2	*tmp;

	if (!proc)
		return (false);
	tmp = proc->outfiles;
	while (tmp)
	{
		file = (t_file *)tmp->data;
		if (valid_filepath(file->name, file->mode))
			file->fd = open(file->name, file->mode);
		else
			file->fd = open(file->name, file->mode, 0644);
		if (file->fd == -1)
			return (perror("minishell: "), outfile_exit(proc));
		tmp = tmp->next;
	}
	return (true);
}

int	open_proc_infiles(t_proc *proc)
{
	t_file	*file;
	t_list2	*tmp;

	if (!proc)
		return (false);
	tmp = proc->infiles;
	while (tmp)
	{
		file = (t_file *)tmp->data;
		if (file->mode != -42)
			file->fd = open(file->name, file->mode);
		if (file->fd == -1 && file->mode != -42)
			return (perror("minishell"), infile_exit(proc));
		tmp = tmp->next;
	}
	return (true);
}

static int	outfile_exit(t_proc *proc)
{
	t_file	*file;
	t_list2 *tmp;

	tmp = (proc->outfiles);
	while (tmp)
	{
		file = tmp->data;
		if (file->mode != -42 && file->fd != -1)
			close(file->fd);
		tmp = tmp->prev;
	}
	lst_destroy2(proc->outfiles, del_file_node);
	file = new_file();
	proc->outfiles = new_node2(file, del_file_node);
	if (proc->outfiles || !file)
		return (lst_destroy2(proc->outfiles, del_file_node), false);
	file->fd = open("/dev/null", O_RDWR);
	file->name = ft_strdup("/dev/null");
	if (!file->fd || !file->name)
		exit(EXIT_FAILURE);
	return (true);
}

static int	infile_exit(t_proc *proc)
{
	t_file	*file;
	t_list2 *tmp;
	t_list2	*tmp2;

	tmp = (proc->infiles)->prev;
	tmp2 = first_node(proc->infiles);
	while (tmp)
	{
		file = tmp->data;
		if (file->mode != -42 && file->fd != -1)
			close(file->fd);
		tmp = tmp->prev;
	}
	lst_destroy2(tmp2, del_file_node);
	lst_destroy2(proc->outfiles, del_file_node);
	proc->outfiles = NULL;
	file = new_file();
	proc->infiles = new_node2(file, del_file_node);
	if (!proc->infiles || !file)
		return (lst_destroy2(proc->infiles, del_file_node), false);
	file->fd = open("/dev/null", O_RDWR);
	file->name = ft_strdup("/dev/null");
	if (!file->fd || !file->name)
		exit(EXIT_FAILURE);
	return (false);
}
