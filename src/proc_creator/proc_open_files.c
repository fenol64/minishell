/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_open_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:14:50 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/02 11:00:01 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static int	infile_exit(t_list2 *infiles);

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
	while (tmp2)
	{
		file = (t_file *)tmp->data;
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
		file->fd = open(file->name, file->mode);
		if (file->fd == -1)
			return (perror("minishell: "), infile_exit(&tmp));
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
		if (file->fd == -1)
			return (perror("minishell: "), infile_exit(&tmp));
		tmp = tmp->next;
	}
	return (true);
}

static int	infile_exit(t_list2 **infiles)
{
	t_file	*file;
	t_list2 *tmp;
	t_list2	*tmp2;

	tmp = (*infiles)->prev;
	tmp2 = first_node(*infiles);
	while (tmp)
	{
		file = tmp->data;
		if (file->mode != -42 && file->fd != -1)
			close(file->fd);
		tmp = tmp->prev;
	}
	lst_destroy2(tmp2, del_file_node);
	file = new_file();
	*infiles = new_node2(file, del_file_node);
	if (!*infiles || !file)
		return (lst_destroy2(*infiles, del_file_node), false);
	file->fd = open("/dev/null", O_RDWR);
	file->name = ft_strdup("/dev/null");
	if (!file->fd || !file->name)
		exit(EXIT_FAILURE);
	return (true);
}