/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:35:58 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/21 15:40:39 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stuff/tmp.h"

t_token	*new_token(char *value, int type, void (*del)(void *))
{
	t_token	*token;

	token = malloc(sizeof * token);
	if (!token)
	{
		if (del)
			del(value);
		return(perror(__func__), NULL);
	}
	token->value = value;
	token->type = type;
	return (token);
}

void	free_token(t_token *token, void (*del)(void *))
{
	if (del)
		del(token->value);
	free(token);
}