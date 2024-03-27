/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split_secondary.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:37:05 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/27 10:31:16 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

static char	*arg_helper(const char *str)
{
	char		*arg;
	char		*quote;
	const char	*delimiter = " \n\f\t\r\v|'\"<>$";

	if (ft_incharset(*str, "\"'") && enclosed_in_quotes(str))
		arg = ft_strpdup(str, ft_strchr(str + 1, *str) + 1);
	else if (is_operator(str))
		arg = ft_strndup(str, ft_strlen(is_operator(str)));
	else if (*str == '$')
		arg = ft_strpdup(str, ft_strchrset(str + 1, delimiter));
	else
	{
		quote = ft_strchrset(str + 1, "\"'");
		if (quote && ft_strchrset(quote + 1, "\"'"))
			arg = ft_strpdup(str, ft_strchrset(str + 1, delimiter));
		else
			arg = ft_strpdup(str, ft_strchrset(str, " \n\f\t\r\v|<>$"));
	}
	return (arg);
}

static t_list2	*get_split(const char *str, t_list2 **list)
{
	char	*arg;
	t_list2	*node;

	arg = arg_helper(str);
	node = new_node2(arg, free);
	lst_append2(list, node);
	if (!node || !node->data)
	{
		if (!node)
			perror(__func__);
		return (NULL);
	}
	return (node);
}

t_list2	*input_split2(t_token *token)
{
	size_t	i;
	t_list2	*new_list;
	t_list2	*node;

	if (!token)
		return (ft_perror(__func__, ARGNULL), NULL);
	new_list = NULL;
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] && !ft_isspace(token->value[i]))
		{
			node = get_split(&token->value[i], &new_list);
			if (!node)
			{
				node = first_node(new_list);
				return (lst_destroy2(node, free), NULL);
			}
			i += ft_strlen((char *)node->data);
		}
		else
			i++;
	}
	return (first_node(new_list));
}

static const char	*delimet(int extra);

t_list2	*input_exp_split(const char *str)
{
	size_t	i;
	t_list2	*new_list;
	t_list2	*node;
	char	*token;

	if (!*str)
		return (new_node2(ft_strdup(""), free));
	new_list = NULL;
	i = 0;
	while (str[i])
	{
		if (ft_incharset(str[i], "'\""))
			token = ft_strpdup(&str[i], &str[i + 1]);
		else if (str[i] == '$')
			token = ft_strpdup(&str[i], ft_strchrset(&str[i + 1], delimet(1)));
		else
			token = ft_strpdup(&str[i], ft_strchrset(&str[i + 1], delimet(0)));
		node = new_node2(token, free);
		if (!token || !node)
			return (lst_destroy2(first_node(new_list), free), NULL);
		lst_append2(&new_list, node);
		i += ft_strlen(token);
	}
	return (first_node(new_list));
}

static const char	*delimet(int extra)
{
	if (extra)
		return (" \n\t\f\r\v$'\"");
	return (" \n\t\f\r\v$");
}
