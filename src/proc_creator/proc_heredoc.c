/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:03:58 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/19 13:55:14 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static char		*return_doc(t_list2 *tmp, char **name, t_main *main);
static t_list2	*expand_line(t_list2 *node, t_main *main);
static t_list2	*append_line(t_list2 **tmp, char **line, int exp, t_main *main);

char	*get_here_doc(t_file *file, t_main *main)
{
	int		expand;
	char	*del;
	char	*line;
	t_list2	*tmp;

	if (g_signal == SIGINT)
		return (NULL);
	tmp = NULL;
	expand = has_quote(file->name);
	del = remove_quotes(file->name);
	file->name = NULL;
	if (!del)
		return (perror(__func__), NULL);
	while (true)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (free(line), free(del), lst_destroy2(tmp, free), NULL);
		if (!line || strcmp(del, line) == 0)
			return (free(line), free(del), return_doc(tmp, &file->name, main));
		if (!append_line(&tmp, &line, expand, main))
			return (free(del), NULL);
	}
	return (NULL);
}

static char	*return_doc(t_list2 *tmp, char **name, t_main *main)
{
	if (tmp)
		*name = ft_strjoinlst(tmp);
	else
		*name = ft_strdup("");
	if (!*name)
	{
		ft_perror(__func__, "HERE DOCUMENT FATAL ERROR!\n");
		lst_destroy2(tmp, free);
		free_main(main);
		exit(-42);
	}
	return (lst_destroy2(tmp, free), *name);
}

static t_list2	*expand_line(t_list2 *node, t_main *main)
{
	void	*old;

	if (!node)
		return (NULL);
	old = node->data;
	node->data = hdoc_expand((char *)node->data, main);
	free(old);
	return (node);
}

static t_list2	*append_line(t_list2 **tmp, char **line, int exp, t_main *main)
{
	t_list2	*node;

	node = new_node2(ft_strjoin(*line, "\n"), free);
	if (exp == 0)
		node = expand_line(node, main);
	lst_append2(tmp, node);
	free(*line);
	if (!node)
		return (lst_destroy2(*tmp, free), NULL);
	*line = NULL;
	return (node);
}
