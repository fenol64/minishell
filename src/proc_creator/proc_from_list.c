/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_from_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:08:07 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/25 10:10:28 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static size_t	cmd_count(t_list2 *input_list);
static void		add_file(t_list2 **redi_list, t_list2 *node, int mode);
static int		get_proc_redirections(t_proc *proc, t_list2 *input_list);
static int		append_to_proc(t_proc *procs, t_token *token,t_list2 *list);

t_proc	**init_procs(t_list2 *list, t_main *main)
{
	int		index;

	index = cmd_count(list);
	main->procs = ft_calloc(sizeof(t_proc *), index + 1);
	if (!main->procs)
		return (perror(__func__), NULL);
	while (index)
	{
		index--;
		main->procs[index] = new_proc(main);
		if (!main->procs[index])
			return (free_proc_list(main->procs, free), NULL);
	}
	index = 0;
	while (list)
	{
		if (!append_to_proc(main->procs[index], (t_token *)list->data, list))
			return (free_proc_list(main->procs, free), NULL);
		else if (((t_token *)list->data)->type == PIPE)
			index++;
		list = list->next;
	}
	return (main->procs);
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
	file->name = ft_strdup(((t_token *)input_list->data)->value);
	if (!file->name)
		return (free_file(file, del_file_node), false);
	if (token->type == INPUT_ARG)
		add_file(&proc->infiles, node, O_RDONLY);
	else if (token->type == OUTPUT_ARG)
		add_file(&proc->outfiles, node, O_CREAT | O_TRUNC | O_WRONLY);
	else if (token->type == APPEND_ARG)
		add_file(&proc->outfiles, node, O_CREAT | O_APPEND | O_WRONLY);
	else if (token->type == HERE_DOC_ARG)
		add_file(&proc->infiles, node, -42);
	return (true);
}

static size_t	cmd_count(t_list2 *input_list)
{
	t_token	*token;
	size_t	count;

	count = 1;
	if (!input_list)
		return (ft_perror(__func__, ARGNULL), 0);
	while (input_list)
	{
		token = (t_token *)input_list->data;
		if (token && token->type == PIPE)
			count++;
		input_list = input_list->next;
	}
	return (count);
}

static void	add_file(t_list2 **redi_list, t_list2 *node, int mode)
{
	t_file	*file;

	file = (t_file *)node->data;
	file->mode = mode;
	lst_append2(redi_list, node);
}

static int	append_to_proc(t_proc *procs, t_token *token, t_list2 *list)
{
	t_list2	*node;

	if (token && token->type == ARG)
	{
		node = new_node2(ft_strdup(token->value), free);
		lst_append2(&procs->argv, node);
		if (!node || !node->data)
			return (false);
	}
	else if (token && operator_type(token))
	{
		if (!get_proc_redirections(procs, list))
			return (false);
	}
	return (true);
}
