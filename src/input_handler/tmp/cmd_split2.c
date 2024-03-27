/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:29:34 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/14 14:24:38 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*arg_helper(const char *str)
{
	char	*arg;
	char	*quote;
	const char	*delimiter = " \n\f\t\r\v|'\"<>$";

	if (ft_incharset(*str, "\"'") && enclosed_in_quotes(str))
		arg = ft_strpdup(str, ft_strchr(str + 1, *str) + 1);
	else if (is_operator(str))
		arg = ft_strndup(str, ft_strlen(is_operator(str)));
	else if (*str == '$')
		arg = ft_strpdup(str, ft_strchset(str + 1, delimiter));
	else
	{
		quote = ft_strchset(str + 1, "\"'");
		if (quote && ft_strchset(quote + 1, "\"'"))
			arg = ft_strpdup(str, ft_strchset(str + 1, delimiter));
		else
			arg = ft_strpdup(str, ft_strchset(str, " \n\f\t\r\v|<>$"));
	}
	return (arg);
}
static t_list2	*get_split(const char *str, t_list2 **list)
{
	char	*arg;
	t_list2	*node;
	t_list2	*start;

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

t_list2	*ft_cmd_split_alt(const char *str)
{
	size_t	i;
	t_list2	*new_list;
	t_list2	*node;

	if (!str)
		return (ft_perror(__func__, ARG_NULL), NULL);
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
				return (lst_clear2(&node, free), NULL);
			}
			i += ft_strlen((char *)node->data);
		}
		else
			i++;
	}
	return (first_node(new_list));
}
