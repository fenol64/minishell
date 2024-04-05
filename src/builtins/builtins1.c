/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:12:51 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/05 13:25:01 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ts_putstr(const char *str)
{
	size_t	size;

	size = ft_strlen(str);
	write(STDOUT_FILENO, str, size * sizeof(char));
}

int	ft_echo(t_proc *proc, t_main *main)
{
	t_list2	*args;
	char	*tmp;
	char	*str;
	char	*end;

	end = "\n";
	args = proc->argv->next;
	if (!proc->argv->next)
		return (write(STDOUT_FILENO, end, sizeof(char)), 0);
	if (lst_len2(proc->argv) > 2 && !ft_strcmp((char *)args->data, "-n"))
	{
		args = args->next;
		end = "";
	}
	str = ft_strjoinlstsep(args, " ");
	tmp = str;
	str = ft_strjoin(str, end);
	get_exit_str(1, main->exit_status);
	if (!str || !tmp)
		return (free(str), free(tmp), 1);
	ts_putstr(str);
	get_exit_str(0, main->exit_status);
	return (free(str), free(tmp), 0);
}

int	ft_cd(t_proc *proc, t_main *main)
{
	char		*target_dir;
	static char	oldpath[PATH_MAX];

	get_exit_str(1, main->exit_status);
	if (!proc || lst_len2(proc->argv) < 2)
		return (ft_perror("", "Too few arguments\n"));
	getcwd(oldpath, PATH_MAX);
	target_dir = (char *)proc->argv->next->data;
	if (chdir(target_dir) == -1)
		perror(target_dir);
	else
	{
		update_envp(main->envp, "OLDPWD", oldpath);
		getcwd(oldpath, PATH_MAX);
		update_envp(main->envp, "PWD", oldpath);
		get_exit_str(0, main->exit_status);
	}
	*oldpath = '\0';
	return (0);
}
