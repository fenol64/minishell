/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:39:53 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/26 15:06:32 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

static int	classify_arg(t_list2 *list);

int	enclosed_in_quotes(const char *str)
{
	const char	*quotes = "\"'"; 

	return (ft_incharset(*str, quotes) && ft_strchr(str + 1, *str));
}

t_tk_name	classify_token(const char *str, t_list2	*list)
{
	size_t		index;
	const char	*set[] = {">>", "<<", ">", "<", "|", NULL};

	if (!str)
		return (ft_perror(__func__, ARGNULL), -1);
	index = 0;
	while (set[index])
	{
		if (ft_strncmp(str, set[index], ft_strlen(set[index])) == 0)
		{
			if (!ft_strcmp(set[index], ">"))
				return (OUTPUT);
			else if (!ft_strcmp(set[index], "<"))
				return (INPUT);
			else if (!ft_strcmp(set[index], ">>"))
				return (APPEND);
			else if (!ft_strcmp(set[index], "<<"))
				return (HERE_DOC);
			else if (!ft_strcmp(set[index], "|"))
				return (PIPE);
		}
		index++;
	}
	return (classify_arg(list));
}

const char	*is_operator(const char *str)
{
	size_t		index;
	const char	*set[] = {">>", "<<", ">", "<", "|", NULL};

	if (!str)
		return (NULL);
	index = 0;
	while (set[index])
	{
		if (ft_strncmp(str, set[index], ft_strlen(set[index])) == 0)
			return (set[index]);
		index++;
	}
	return (NULL);
}

static int	classify_arg(t_list2 *list)
{
	t_token	*tmp;

	if (list && list->prev)
	{
		tmp = (t_token *)list->prev->data;
		if (!ft_strcmp(tmp->value, ">"))
			return (OUTPUT_ARG);
		else if (!ft_strcmp(tmp->value, "<"))
			return (INPUT_ARG);
		else if (!ft_strcmp(tmp->value, ">>"))
			return (APPEND_ARG);
		else if (!ft_strcmp(tmp->value, "<<"))
			return (HERE_DOC_ARG);
	}
	return (ARG);
}

char	*ft_strjoin_token_lst(t_list2 *list)
{
	char	*joined;
	size_t	len;
	t_list2	*tmp;

	len = 0;
	tmp = list;
	if (!list)
		return (ft_perror(__func__, ARGNULL), NULL);
	while (tmp)
	{
		len += ft_strlen(((t_token *)tmp->data)->value);
		tmp = tmp->next;
	}
	joined = malloc((len + 1) * sizeof(char));
	*joined = '\0';
	if (!joined)
		return (perror(__func__), NULL);
	while (list)
	{
		ft_strcat(joined, ((t_token *)list->data)->value);
		list = list->next;
	}
	return (joined);
}
