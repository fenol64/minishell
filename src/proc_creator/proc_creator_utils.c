/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_creator_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:03:58 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/01 12:34:39 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static char	*quit_hdoc(t_list2 *tmp, char **name);
static int	has_quote(const char *str);

void	del_file_node(void *arg)
{
	free_file((t_file *)arg, free);
}

char	*get_here_doc(t_file *file)
{
	int		expand;
	char	*delimeter;
	char	*line;
	t_list2	*tmp;
	t_list2	*node;

	tmp = NULL;
	expand = has_quote(file->name);
	delimeter = file->name;
	while (true)
	{
		line = readline("> ");
		if (!line)
			return (lst_destroy2(tmp, free), NULL);
		if (strcmp(delimeter, line) == 0)
			return (free(line), free(delimeter), quit_hdoc(tmp, &file->name));
		node = new_node2(ft_strjoin(line, "\n"), free);
		lst_append2(&tmp, node);
		free(line);
		if (!node)
			return (lst_destroy2(tmp, free), NULL);
	}
	return (NULL);
}

static char	*quit_hdoc(t_list2 *tmp, char **name)
{
	if (tmp)
		*name = ft_strjoinlst(tmp);
	else
		*name = ft_strdup("");
	if (!*name)
	{
		ft_perror("HERE DOCUMENT FATAL ERROR!\n");
		exit(EXIT_FAILURE);
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
