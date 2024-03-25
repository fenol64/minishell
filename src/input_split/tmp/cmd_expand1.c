/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:50:58 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/21 12:35:58 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes(char *str)
{
	char *tmp;

	if (enclosed_in_quotes(str))
	{
		tmp = ft_strpdup(str + 1, ft_strchr(str + 1, *str));
		free(str);
		str = tmp;
	}
	else
	{
		tmp = ft_strdup(str);
		free(str);
		str = tmp;
	}
	return (tmp);
}
static char	*expand_str(char *str)
{
	char	*tmp;
	char	*new;

	tmp = str;
	if (*str != '$')
	{
		new = ft_strdup(str);
		free(tmp);
		return (new);
	}
	else if (str[0] == '$' && str[1] == '\0')
	{
		new = ft_strdup(str);
		free(tmp);
		return (new);
	}
	new = get_env(str + 1);
	return (free(tmp), ft_strdup(new));
}

char *get_env(char *name)
{
	char *new;

	if (!name)
		return (ft_perror(__func__, ARGNULL), NULL);
	new = getenv(name);
	if (!new)
		new = "";
	return (new);
}

void	expand_args(t_list2 *list)
{
	t_list2	*tmp;
	t_list2	*tmp_list;

	while (list)
	{
		if (enclosed_in_quotes((char *)list->data) && *(char *)list->data == '\'')
		{
			list->data = (void *)remove_quotes((char *)list->data);
			list = list->next;
			continue ;
		}
		list->data = (void *)remove_quotes((char *)list->data);
		tmp_list = ft_cmd_exp_split((char *)list->data);
		tmp = tmp_list;
		while (tmp)
		{
			tmp->data = (void *)expand_str((char *)tmp->data);
			tmp = tmp->next;
		}
		free(list->data);
		list->data = (void *)ft_strjoinlst(tmp_list);
		lst_clear2(&tmp_list, free);
		list = list->next;
	}
}

char	*ft_strjoinlst(t_list2 *list)
{
	char	*joined;
	size_t	len;
	t_list2	*tmp;

	len = 0;
	tmp = list;
	if (!list)
		return (ft_perror(__func__, ARG_NULL), NULL);
	while (tmp)
	{
		len += ft_strlen((char *)tmp->data);
		tmp = tmp->next;
	}
	joined = malloc((len + 1) * sizeof(char));
	*joined = '\0';
	if (!joined)
		return (perror(__func__), NULL);
	while (list)
	{
		ft_strcat(joined, (char *)list->data);
		list = list->next;
	}
	return (joined);
}
