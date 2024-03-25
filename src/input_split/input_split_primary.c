/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split_primary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:19:37 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/25 17:00:11 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stuff/tmp.h"

static t_token	*arg_helper(const char *str, t_token *token)
{
	int		in_quotes;
	char	quote;
	int		i;

	i = -1;
	in_quotes = false;
	while (str[++i] && !(!in_quotes && ft_isspace(str[i])))
	{
		if (!in_quotes && enclosed_in_quotes(&str[i]))
		{
			in_quotes = true;
			quote = str[i];
		}
		else if (in_quotes && str[i] == quote)
			in_quotes = false;
		else if (!in_quotes && is_operator(&str[i]))
		{
			if (i == 0)
				i = ft_strlen(is_operator(&str[i]));
			break ;
		}
	}
	if (token)
		token->value = ft_strpdup(str, &str[i]);
	return (token);
}

static t_list2	*get_split(const char *str, t_list2 **list)
{
	t_token	*arg;
	t_list2	*node;

	arg = new_token(NULL, 0, NULL);
	arg = arg_helper(str, arg);
	node = new_node2(arg, free);
	lst_append2(list, node);
	if (arg)
		arg->type = classify_token(arg->value, node);
	if (!node || !node->data)
	{
		if (!node)
			perror(__func__);
		return (NULL);
	}
	return (node);
}

t_list2	*input_split1(const char *str)
{
	size_t	i;
	t_list2	*new_list;
	t_list2	*node;

	if (!str)
		return (ft_perror(__func__, ARGNULL), NULL);
	new_list = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] && !ft_isspace(str[i]))
		{
			node = get_split(&str[i], &new_list);
			if (!node)
			{
				node = first_node(new_list);
				return (lst_destroy2(node, free), NULL);
			}
			i += ft_strlen(((t_token *)node->data)->value);
		}
		else
			i++;
	}
	return (first_node(new_list));
}

char	*get_true_input(t_list2 *primary, char **envp)
{
	t_token	*token;
	t_list2	*arg;
	t_list2	*tmp;
	char	*input;

	tmp = primary;
	if (!primary)
		return (NULL);
	while (tmp)
	{
		token = (t_token *)tmp->data;
		arg = input_split2(token);
		if (!arg)
			return (NULL);
		if (!expand_args(arg, envp, token))
			return (NULL);
		free(token->value);
		token->value = ft_strjoinlst(arg);
		lst_destroy2(arg, free);
		tmp = tmp->next;
	}
	input = ft_strjoinlst_alt(primary);
	return (input);
}

char	*ft_strjoinlst_alt(t_list2 *list)
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