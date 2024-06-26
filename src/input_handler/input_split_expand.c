/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:42:54 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/30 09:57:42 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

static int	expand_single_quotes(t_list2 **list, t_token *token);

char	*ft_getenv(char *name, t_main *main)
{
	char	**envp;
	size_t	var_size;
	size_t	index;

	if (!main || !name || !main->envp)
		return (ft_perror(__func__, ARGNULL), NULL);
	index = 0;
	envp = main->envp;
	if (!ft_strcmp(name, "?"))
		return (main->exit_status);
	while (envp[index])
	{
		if (!ft_strchr(envp[index], '='))
			return (ft_perror(__func__, "Env doesn't have equal sign"), NULL);
		var_size = ft_strlen(name);
		if (!ft_strncmp(envp[index], name, var_size / sizeof(char)))
			return (ft_strchr(envp[index], '=') + sizeof(char));
		index++;
	}
	return ("");
}

char	*remove_quotes(char *str)
{
	char	*tmp;

	if (!str)
		return (ft_perror(__func__, ARGNULL), NULL);
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

static char	*expand_str(char *str, t_main *main)
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
	new = ft_getenv(str + 1, main);
	return (free(tmp), ft_strdup(new));
}

int	expand_args(t_list2 *list, t_main *main, t_token *token)
{
	t_list2	*tmp;
	t_list2	*tmp_list;

	while (list)
	{
		if (expand_single_quotes(&list, token))
			continue ;
		list->data = (void *)remove_quotes((char *)list->data);
		tmp_list = input_exp_split((char *)list->data);
		if (!tmp_list)
			return (lst_destroy2(list, free), false);
		tmp = tmp_list;
		while (tmp)
		{
			tmp->data = (void *)expand_str((char *)tmp->data, main);
			tmp = tmp->next;
		}
		free(list->data);
		list->data = (void *)ft_strjoinlst(tmp_list);
		lst_destroy2(tmp_list, free);
		list = list->next;
	}
	return (true);
}

static int	expand_single_quotes(t_list2 **list, t_token *token)
{
	char	*data;

	if (!list || !(*list)->data)
	{
		ft_perror(__func__, ARGNULL);
		exit(EXIT_FAILURE);
		return (false);
	}
	data = (char *)(*list)->data;
	if (enclosed_in_quotes(data) && *data == '\'')
	{
		if (token->type != HERE_DOC_ARG)
			(*list)->data = (void *)remove_quotes(data);
		*list = (*list)->next;
		return (true);
	}
	return (false);
}
