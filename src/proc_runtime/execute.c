/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:29:25 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/16 10:51:14 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_runtime.h"

static int	is_directory(const char *path, t_main *main)
{
	struct stat	path_stat;

	if (!path)
	{
		free_main(main);
		ft_perror(__func__, ARGNULL);
		exit(EXIT_FAILURE);
	}
	if (stat(path, &path_stat) == 0)
	{
		if (S_ISREG(path_stat.st_mode))
			return (false);
		else if (S_ISDIR(path_stat.st_mode))
			return (true);
	}
	return (false);
}

//	execute a command specified in proc's argv using execve
int	execute_builtin(t_proc *proc, t_main *main)
{
	if (!proc || !main || !proc->argv || !proc->argv->data)
		return (ft_perror(__func__, ARGINV), EXIT_FAILURE);
	if (!ft_strcmp(proc->argv->data, "echo"))
		return (ft_echo(proc, main));
	if (!ft_strcmp(proc->argv->data, "cd"))
		return (ft_cd(proc, main));
	if (!ft_strcmp(proc->argv->data, "pwd"))
		return (ft_pwd(proc, main));
	if (!ft_strcmp(proc->argv->data, "unset"))
		return (ft_unset(proc, main));
	if (!ft_strcmp(proc->argv->data, "export"))
		return (ft_export(proc, main));
	if (!ft_strcmp(proc->argv->data, "env"))
		return (ft_env(proc, main));
	if (!ft_strcmp(proc->argv->data, "exit"))
		return (ft_exit(proc, main));
	return (ft_perror(__func__, "What did you do!?"), EXIT_FAILURE);
}

int	execute_child(t_proc *proc, t_main *main)
{
	int		status;
	char	**argv;

	if (!proc || !proc->argv)
		return (ft_perror(__func__, ARGINV), EXIT_FAILURE);
	status = 126;
	if (is_builtin(proc->argv->data))
		return (execute_builtin(proc, main));
	if (is_directory((char *)proc->argv->data, main))
	{
		errno = EISDIR;
		ft_perror(proc->argv->data, "Is a directory");
		exit(status);
	}
	argv = matrix_from_lst(proc->argv);
	if (!argv)
		exit(EXIT_FAILURE);
	execve(argv[0], argv, main->envp);
	if (errno == ENOENT)
		ft_perror((char *)proc->argv->data, "command not found");
	else if (errno && errno != ENOENT)
		perror((char *)proc->argv->data);
	ft_free_matrix(argv);
	free_main(main);
	exit(status + (errno == ENOENT));
}
