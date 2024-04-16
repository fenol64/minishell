/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_creator_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:03:58 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/16 12:39:00 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static int		has_quote(const char *str);
static char		*quit_hdoc(t_list2 *tmp, char **name, t_main *main);
static t_list2	*expand_line(t_list2 *node, t_main *main);

char	*get_here_doc(t_file *file, t_main *main)
{
	int		expand;
	char	*del;
	char	*line;
	t_list2	*tmp;
	t_list2	*node;

	tmp = NULL;
	expand = has_quote(file->name);
	del = file->name;
	while (true)
	{
		line = readline("> ");
		if (!line)
			return (free(line), free(del), quit_hdoc(tmp, &file->name, main));
		if (strcmp(del, line) == 0)
			return (free(line), free(del), quit_hdoc(tmp, &file->name, main));
		node = new_node2(ft_strjoin(line, "\n"), free);
		if (expand == 0)
			node = expand_line(node, main);
		lst_append2(&tmp, node);
		free(line);
		if (!node)
			return (lst_destroy2(tmp, free), NULL);
	}
	return (NULL);
}

static char	*quit_hdoc(t_list2 *tmp, char **name, t_main *main)
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

static int	has_quote(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (ft_incharset(str[index], "\"'"))
			return (true);
		index++;
	}
	return (false);
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
