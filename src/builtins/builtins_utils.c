/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 12:55:53 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ts_putstr(const char *str)
{
	int		status;
	size_t	size;

	size = ft_strlen(str);
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