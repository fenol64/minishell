/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:12:51 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/09 10:30:23 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(t_proc *proc, t_main *main)
{
	t_list2	*args;
	char	*tmp;
	char	*str;
	char	*end;

	end = "\n";
	args = proc->argv->next;
	if (args && !ft_strcmp((char *)args->data, "-n"))
	{
		args = args->next;
		end = "";
	}
	if (!proc->argv->next || !args)
		return (write(STDOUT_FILENO, end, sizeof(char)), EXIT_SUCCESS);
	str = ft_strjoinlstsep(args, " ");
	tmp = str;
	str = ft_strjoin(str, end);
	get_exit_str(1, main->exit_status);
	if (!str || !tmp)
		return (free(str), free(tmp), EXIT_FAILURE);
	if (ts_putstr(str) == -1)
		return (free(str), free(tmp), EXIT_FAILURE);
	get_exit_str(0, main->exit_status);
	return (free(str), free(tmp), EXIT_SUCCESS);
}

int	ft_cd(t_proc *proc, t_main *main)
{
	char		*target_dir;
	static char	oldpath[PATH_MAX];

	get_exit_str(1, main->exit_status);
	if (!proc || !proc->argv)
		return (ft_perror("", ARGINV), EXIT_FAILURE);
	if (lst_len2(proc->argv) > 2)
		return (ft_perror("minishell: cd", "too many arguments"), 1);
	getcwd(oldpath, PATH_MAX);
	target_dir = ft_getenv("HOME", main);
	if (!target_dir)
		target_dir = "";
	if (proc->argv->next)
		target_dir = (char *)proc->argv->next->data;
	if (!*target_dir)
		return (get_exit_str(0, main->exit_status), EXIT_SUCCESS);
	if (chdir(target_dir) == -1)
		return (perror(target_dir), EXIT_FAILURE);
	main->envp = update_envp(main->envp, "OLDPWD", oldpath);
	getcwd(oldpath, PATH_MAX);
	main->envp = update_envp(main->envp, "PWD", oldpath);
	get_exit_str(0, main->exit_status);
	*oldpath = '\0';
	return (EXIT_SUCCESS);
}

int	ft_pwd(t_proc *proc, t_main *main)
{
	char		*option;
	static char	cwd[PATH_MAX];

	get_exit_str(1, main->exit_status);
	option = "";
	if (!proc || !proc->argv)
		return (ft_perror(__func__, ARGINV), EXIT_FAILURE);
	if (proc->argv && proc->argv->next)
		option = (char *)proc->argv->next->data;
	if (option[0] == '-' && option[1])
	{
		ft_perror(option, "invalid option");
		return (EXIT_FAILURE);
	}
	getcwd(cwd, PATH_MAX * sizeof(char));
	if (ts_putstr(cwd) == -1)
		return (EXIT_FAILURE);
	get_exit_str(0, main->exit_status);
	return (EXIT_SUCCESS);
}

int	ft_exit(t_proc *proc, t_main *main)
{
	get_exit_str(1, main->exit_status);
	if (!proc || !main || !proc->argv)
		return (ft_perror(__func__, ARGINV), EXIT_FAILURE);
	else if (lst_len2(proc->argv) > 1)
		ft_perror("exit\nminishel: exit", "too many arguments");
	else
		get_exit_str(0, main->exit_status);
	exit(ft_atoi(main->exit_status));
	return (EXIT_FAILURE);
}

int	ft_env(t_proc *proc, t_main *main)
{
	size_t	index;

	get_exit_str(1, main->exit_status);
	if (!proc || !main || !proc->argv || !main->envp)
		return (ft_perror(__func__, ARGINV), EXIT_FAILURE);
	else if (lst_len2(proc->argv) > 1)
		ft_perror("minishel: env", "too many arguments");
	index = 0;
	while (main->envp[index])
	{
		if (ts_putstr(main->envp[index]) == -1)
			return (EXIT_FAILURE);
		index++;
	}
	get_exit_str(0, main->exit_status);
	return (EXIT_SUCCESS);
}
