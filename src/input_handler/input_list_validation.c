/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:15:50 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/27 14:05:26 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

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
			return (false);
		else if (token2 && is_operator(token->value) && is_operator(token2->value))
			return (ft_unxerror(token2->value), false);
		else if (is_operator(token->value) && !tmp->next)
			return (ft_unxerror("newline"), false);
		token2 = NULL;		
		tmp = tmp->next;
	}
	return (true);
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