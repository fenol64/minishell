/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_strsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:33:11 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/14 14:36:17 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list2	*ft_cmd_exp_split(const char *str)
{
	size_t	i;
	t_list2	*new_list;
	t_list2	*node;
	char	*token;

	if (!str)
		return (ft_perror(__func__, ARG_NULL), NULL);
	new_list = NULL;
	i = 0;
	while (str[i])
	{
		if (enclosed_in_quotes(&str[i]))
			token = ft_strpdup(&str[i], ft_strchr(&str[i + 1], str[i]) + 1);
		else
			token = ft_strpdup(&str[i], ft_strchset(&str[i + 1], " \n\t\f\r\v$"));
		node = new_node2(token, free);
		if (!token || !node)
		{
			node = first_node(new_list);
			return (lst_clear2(&node, free), NULL);
		}
		lst_append2(&new_list, node);
		i += ft_strlen(token);
	}
	return (first_node(new_list));
}
