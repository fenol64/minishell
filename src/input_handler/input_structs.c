/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:35:58 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/01 15:19:12 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

t_main	*new_main(char **envp)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
		return (perror(__func__), NULL);
	main->std_in = dup(STDIN_FILENO);
	main->std_out = dup(STDOUT_FILENO);
	if (main->std_in == -1 || main->std_out == -1)
		return (free_main(main), NULL);
	main->envp = envp;
	ft_memset(main->exit_status, '\0', EXSTR * sizeof(char));
	main->exit_status[0] = '0';
	return (main);
}

void	free_main(t_main *main)
{
	if (!main)
		return ;
	close(main->std_out);
	close(main->std_in);
	free(main);
}

t_token	*new_token(char *value, int type, void (*del)(void *))
{
	t_token	*token;

	token = malloc(sizeof * token);
	if (!token)
	{
		if (del)
			del(value);
		return (perror(__func__), NULL);
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

void	free_token_node(void *arg)
{
	t_token	*token;

	token = (t_token *)arg;
	free_token(token, free);
}
