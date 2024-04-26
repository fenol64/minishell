/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_filepaths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:00:56 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/26 12:38:13 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static int	has_permission(const char *path, int mode);

int	is_builtin(char *cmd)
{
	size_t				index;
	static const char	*builtins[] = {
		"cd", "pwd", "env", "export",
		"unset", "echo", "exit", NULL
	};

	index = 0;
	if (!cmd)
		return (false);
	while (builtins[index])
	{
		if (ft_strcmp(builtins[index], cmd) == 0)
			return (true);
		index++;
	}
	return (false);
}

int	valid_path(const char *path, int mode)
{
	return (has_permission(path, mode));
}

int	valid_folder(const char *path, int mode)
{
	struct stat	path_stat;

	if (!path)
		return (false);
	if (has_permission(path, mode) == false)
		return (false);
	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (true);
		else if (S_ISREG(path_stat.st_mode))
			return (false);
		return (false);
	}
	perror(__func__);
	return (false);
}

int	valid_filepath(const char *path, int mode)
{
	struct stat	path_stat;

	if (!path)
		return (false);
	if (has_permission(path, mode) == false)
		return (false);
	if (stat(path, &path_stat) == 0)
	{
		if (S_ISREG(path_stat.st_mode))
			return (true);
		else if (S_ISDIR(path_stat.st_mode))
			return (false);
	}
	perror(__func__);
	return (false);
}

static int	has_permission(const char *path, int mode)
{
	if (!path)
		return (false);
	if (access(path, mode) == 0)
		return (true);
	return (false);
}
