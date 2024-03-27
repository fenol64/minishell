/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:42:54 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/26 15:06:13 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

static char	*ft_getenv(char *name, char **envp)
{
	size_t	index;

	if (!envp || !*envp || !name)
		return (ft_perror(__func__, ARGNULL), NULL);
	index = 0;
	while (envp[index])
	{
		if (!ft_strncmp(envp[index], name, ft_strlen(name)))
			return (ft_strchr(envp[index], '=') + 1);
		index++;
	}
	return ("");
}

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
static char	*expand_str(char *str, char **envp)
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
	new = ft_getenv(str + 1, envp);
	return (free(tmp), ft_strdup(new));
}

int	expand_args(t_list2 *list, char **envp, t_token *token)
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
		tmp_list = input_exp_split((char *)list->data);
		if (!tmp_list)
			return (lst_destroy2(list, free), false);
		tmp = tmp_list;
		while (tmp)
		{
			if (token->type != HERE_DOC_ARG)
				tmp->data = (void *)expand_str((char *)tmp->data, envp);
			tmp = tmp->next;
		}
		free(list->data);
		list->data = (void *)ft_strjoinlst(tmp_list);
		lst_destroy2(tmp_list, free);
		list = list->next;
	}
	return (true);
}

char	*ft_strjoinlst(t_list2 *list)
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