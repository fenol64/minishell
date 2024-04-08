/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/08 16:02:17 by paulhenr         ###   ########.fr       */
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

int	ts_putstr(const char *str)
{
	int		status;
	size_t	size;

	size = ft_strlen(str);
		return (-1);
	status = write(STDOUT_FILENO, str, size * sizeof(char));
	if (status == -1)
		perror(__func__);
	return (status);
}

int	has_invalid_opt(t_list2 *argv)
{
	char	*arg;

	if (!argv)
		return (ft_perror(__func__, ARGNULL), true);
	if (!argv->next)
		return (false);
	arg = (char *)argv->next->data;
	if (!arg)
		return (ft_perror(__func__, ARGINV), true);
	if (arg[0] == '-' && arg[1])
		return (true);
	return (false);
}