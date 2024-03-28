/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_from_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:08:07 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/28 16:24:27 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static int		get_proc_redirections(t_proc *proc, t_list2 *input_list);
static size_t	cmd_count(t_list2 *input_list);

t_proc	**get_procs(t_list2 *input_list, char **envp)
{
	t_list2	*node;
	t_token	*token;
	t_proc	**procs;
	size_t	index;

	procs = ft_calloc(sizeof(t_proc *), cmd_count(input_list) + 1);
	if (!procs)
		return (perror(__func__), NULL);
	index = 0;
	procs[index] = new_proc();
	if (!procs[index])
		return (free_proc_list(procs, free), NULL);
	while (input_list)
	{
		token = (t_token *)input_list->data;
		if (token && token->type == ARG)
		{
			node = new_node2(ft_strdup(token->value), free);
			lst_append2(&(procs[index]->argv), node);
			if (!node || !node->data)
				return (free_proc_list(procs, free), NULL);
		}
		else if (token && operator_type(token))
		{
			if (!get_proc_redirections(procs[index], input_list))
				return (free_proc_list(procs, free), NULL);
		}
		else if (token && token->type == PIPE)
		{
			index++;
			procs[index] = new_proc();
			if (!procs[index])
				return (free_proc_list(procs, free), NULL);
		}
		input_list = input_list->next;
	}
	(void)envp;
	return (procs);
}

static int	get_proc_redirections(t_proc *proc, t_list2 *input_list)
{
	t_file	*file;
	t_list2	*node;
	t_token	*token;

	node = NULL;
	input_list = input_list->next;
	token = (t_token *)(input_list)->data;
	file = new_file();
	if (!file)
		return (false);
	node = new_node2(file, free);
	if (!node)
		return (free_file(file, del_file_node), false);
	file->name =  ft_strdup(((t_token *)input_list->data)->value);
	if (!file->name)
		return (free_file(file, del_file_node), false);
	if (token->type == INPUT_ARG)
	{
		lst_append2(&proc->infiles, node);
		file->mode = O_RDONLY;
	}
	else if (token->type == OUTPUT_ARG)
	{
		lst_append2(&proc->outfiles, node);
		file->mode = O_CREAT | O_TRUNC | O_WRONLY;
	}
	else if (token->type == APPEND_ARG)
	{
		lst_append2(&proc->outfiles, node);
		file->mode = O_CREAT | O_APPEND | O_WRONLY;
	}
	else if (token->type == HERE_DOC_ARG)
	{
		get_here_doc(file);
		lst_append2(&proc->infiles, node);
	}
	return (true);
}

static size_t	cmd_count(t_list2 *input_list)
{
	t_token	*token;
	size_t	count;

	count = 1;
	while (input_list)
	{
		token = (t_token *)input_list->data;
		if (token && token->type == PIPE)
			count++;
		input_list = input_list->next;
	}
	return (count);
}
