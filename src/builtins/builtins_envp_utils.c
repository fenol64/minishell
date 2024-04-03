/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_envp_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/03 14:18:09 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**cpy_envp(char **envp)
{
	char	**cpy;
	size_t	size;

	if (!envp)
		return (ft_perror(__func__, ARGNULL), NULL);
	size = 0;
	while (envp[size])
		size++;
	cpy = malloc(sizeof(char *) * (size + 1));
	if (!cpy)
		return (perror(__func__), NULL);
	size = 0;
	while (envp[size])
	{
		cpy[size] = ft_strdup(envp[size]);
		size++;
	}
	cpy[size] = NULL;
	return (cpy);
}
