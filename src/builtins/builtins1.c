/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:12:51 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/29 12:18:36 by paulhenr         ###   ########.fr       */
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
	char		opt[4];
	char		*joined;
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
		ft_strlcpy(opt, option, 3);
		ft_perror(opt, "invalid option");
		return (EXIT_FAILURE);
	}
	getcwd(cwd, PATH_MAX * sizeof(char));
	joined = ft_strjoin(cwd, "\n");
	if (!joined)
		return (perror(__func__), EXIT_FAILURE);
	if (ts_putstr(joined) == -1)
		return (free(joined), EXIT_FAILURE);
	get_exit_str(0, main->exit_status);
	return (free(joined), EXIT_SUCCESS);
}

int	ft_exit(t_proc *proc, t_main *main)
{
	int	exit_status;

	if (!proc || !main || !proc->argv)
	{
		get_exit_str(1, main->exit_status);
		return (ft_perror(__func__, ARGINV), EXIT_FAILURE);
	}
	if (proc->argv->next && !ft_strnumeric(proc->argv->next->data))
	{
		get_exit_str(2, main->exit_status);
		ft_perror("exit\nminishel: exit", "numeric argument required");
	}
	else if (lst_len2(proc->argv) > 2)
	{
		get_exit_str(130, main->exit_status);
		ft_perror("exit\nminishel: exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	get_exit_str(ft_atoi(proc->argv->next->data), main->exit_status);
	exit_status = ft_atoi(main->exit_status);
	free_main(main);
	exit(exit_status);
	return (EXIT_FAILURE);
}

int	ft_env(t_proc *proc, t_main *main)
{
	char	*joined;
	size_t	index;

	get_exit_str(1, main->exit_status);
	if (!proc || !main || !proc->argv || !main->envp)
		return (ft_perror(__func__, ARGINV), EXIT_FAILURE);
	else if (lst_len2(proc->argv) > 1)
	{
		ft_perror("minishel: env", "too many arguments");
		return (EXIT_FAILURE);
	}
	index = 0;
	while (main->envp[index])
	{
		joined = ft_strjoin(main->envp[index], "\n");
		if (!joined)
			return (perror(__func__), EXIT_FAILURE);
		if (ts_putstr(joined) == -1)
			return (EXIT_FAILURE);
		free(joined);
		index++;
	}
	get_exit_str(0, main->exit_status);
	return (EXIT_SUCCESS);
}
