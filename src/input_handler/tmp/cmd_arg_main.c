/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:37:39 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/21 12:35:37 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_true_prompt(char *input)
{
	t_list2	*tmp;
	t_list2	*tokens;

	if (!input)
		return (ft_perror(__func__, ARGNULL), NULL);
	tokens = ft_cmd_split(input);
	if (!tokens)
		return (NULL);
	tmp = tokens;
	while (tmp)
	{
		
	}
}