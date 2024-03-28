/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:15:50 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/28 15:03:58 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

static int	repeated_operator(t_token *t1, t_token *t2);
static void	ft_unxerror(const char *token);

int	validate_input_list(t_list2 *input_list)
{
	t_token	*token2;
	t_token	*token;
	t_list2	*tmp;

	if (!input_list)
		return (false);
	tmp = input_list;
	token2 = NULL;
	while (tmp)
	{
		if (tmp->next)
			token2 = (t_token *)tmp->next->data;
		token = (t_token *)tmp->data;
		if (!token)
			return (false);
		else if (tmp == input_list && token->type == PIPE)
			return (ft_unxerror("|"), false);
		else if (token2 && repeated_operator(token, token2))
			return (ft_unxerror(token2->value), false);
		else if (operator_type(token) && !tmp->next)
			return (ft_unxerror("newline"), false);
		token2 = NULL;
		tmp = tmp->next;
	}
	return (true);
}

static int	repeated_operator(t_token *t1, t_token *t2)
{
	if (operator_type(t1) && operator_type(t2))
			return (true);
	return (false);
}

static void	ft_unxerror(const char *token)
{
	size_t		size;
	char		*new;
	const char	*err = "minishell: syntax error near unexpected token `";

	size = 0;
	new = ft_strsepjoin(err, token, "'\n");
	if (!new)
	{
		perror(__func__);
		return ;
	}
	size = ft_strlen(new);
	write(STDERR_FILENO, new, size);
	free(new);
}

int	operator_type(t_token *token)
{
	if (token && (token->type == OUTPUT || token->type == INPUT))
		return (true);
	else if (token && (token->type == APPEND || token->type == HERE_DOC))
		return (true);
	return (false);
}