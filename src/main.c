/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:12:21 by fnascime          #+#    #+#             */
/*   Updated: 2024/03/12 15:53:06 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int c, char **v, char **envp)
{
	char	*s;
	(void)c;
	(void)v;
	(void)envp;

	while (1)
	{
		s = readline("minishell$ ");
		if (s == NULL)
			break ;
		if (ft_strlen(s) > 0)
			add_history(s);
		if (ft_strncmp(s, "exit", 4) == 0)
		{
			free(s);
			break ;
		}
		free(s);
	}
}
