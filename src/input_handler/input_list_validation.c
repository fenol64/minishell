/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:15:50 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/27 14:36:01 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

static int	repeated_operator(const char *s1, const char *s2);
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
		else if (token2 && repeated_operator(token->value, token2->value))
			return (ft_unxerror(token2->value), false);
		else if (is_operator(token->value) && !tmp->next)
			return (ft_unxerror("newline"), false);
		token2 = NULL;		
		tmp = tmp->next;
	}
	return (true);
}

static int	repeated_operator(const char *s1, const char *s2)
{
	if (is_operator(s1) && is_operator(s2))
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
