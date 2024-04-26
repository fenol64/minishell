/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split_primary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:19:37 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/26 10:22:01 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

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

static t_list2	*valid_input_list(t_list2 *list, t_main *main)
{
	if (!validate_input_list(list, main))
		return (lst_destroy2(list, free_token_node), NULL);
	return (list);
}

//	Gets a linked list with the parsed and expanded shell prompt input
//	where each node is classified by tokens.
t_list2	*get_true_input(const char *input, t_main *main)
{
	t_list2	*tmp;
	t_list2	*primary;
	t_list2	*tmp_arg;
	t_token	*token;

	primary = input_split1(input);
	if (!primary)
		return (NULL);
	tmp = primary;
	while (tmp)
	{
		token = (t_token *)tmp->data;
		tmp_arg = input_split2(token);
		if (!tmp_arg)
			return (lst_destroy2(primary, free_token_node), NULL);
		if (!expand_args(tmp_arg, main, token))
			return (lst_destroy2(primary, free_token_node), NULL);
		free(token->value);
		token->value = ft_strjoinlst(tmp_arg);
		lst_destroy2(tmp_arg, free);
		if (!token->value)
			return (lst_destroy2(primary, free_token_node), NULL);
		tmp = tmp->next;
	}
	return (valid_input_list(primary, main));
}
