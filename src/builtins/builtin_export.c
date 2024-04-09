/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:30:15 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/09 16:10:33 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	print_exp_envp(char **envp);
static int	validate_assign(char *name);
static char	**get_new_envp(char **envp, const char *entry);

int	validate_export(t_list2	*node)
{
	char	*str;
	char	*name;
	char	*value;
	char	*anchor;

	if (!node || !node->data)
		return (ft_perror(__func__, ARGNULL), false);
	str = (char *)node->data;
	if (*str == '=')
		return (ft_perror(str, "not a valid identifier"), false);
	else if (!*str)
		return (ft_perror("''", "not a valid identifier"), false);
	anchor = ft_strchr(str, '=');
	if (!anchor)
		return (false);
	name = ft_strpdup(str, anchor);
	value = ft_strdup(anchor + 1);
	if (!name || !value)
		return (perror(__func__), free(name), free(value), false);
	if (!validate_assign(name))
		return (free(name), free(value), false);
	free(name);
	free(value);
	return (true);
}

int	ft_export(t_proc *proc, t_main *main)
{
	int		status;
	char	*entry;
	t_list2	*tmp;

	get_exit_str(EXIT_FAILURE, main->exit_status);
	if (has_invalid_opt(proc->argv))
		return (ft_perror("export", "no support for options"), false);
	if (!proc->argv->next)
	{
		status = print_exp_envp(main->envp);
		get_exit_str(status, main->exit_status);
		return (status);
	}
	tmp = proc->argv->next;
	while (tmp)
	{
		entry = (char *)tmp->data;
		if (validate_export(tmp))
			main->envp = get_new_envp(main->envp, entry);
		if (!main->envp)
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	get_exit_str(EXIT_SUCCESS, main->exit_status);
	return (EXIT_SUCCESS);
}

static char	**get_new_envp(char **envp, const char *entry)
{
	char	*name;
	char	*anchor;
	char	*value;
	char	**new_envp;

	anchor = ft_strchr(entry, '=');
	if (!anchor)
	{
		ft_perror("Fatal Error", "Invalid Environment");
		ft_free_matrix(envp);
		return (NULL);
	}
	name = ft_strpdup(entry, anchor);
	if (!name)
		return (false);
	value = ft_strdup(anchor + 1);
	if (!value)
		return (perror(__func__), free(name), NULL);
	new_envp = update_envp(envp, name, value);
	if (!new_envp)
		return (perror(__func__), free(name), free(value), NULL);
	return (free(name), free(value), new_envp);
}

static int	validate_assign(char *name)
{
	size_t	index;

	if (ft_isdigit(*name) || !*name)
		return (ft_perror(name, "not a valid identifier"), false);
	index = 0;
	if (*name == '_')
		index++;
	while (name[index])
	{
		if (!ft_isalnum(name[index]) && name[index] != '_')
			return (ft_perror(name, "not a valid identifier"), false);
		index++;
	}
	return (true);
}

static int	print_exp_envp(char **envp)
{
	char	*tmp;
	size_t	index;

	index = 0;
	while (envp[index])
	{
		tmp = ft_strsepjoin("declare -x ", envp[index], "\n");
		if (!tmp)
			return (EXIT_FAILURE);
		ts_putstr(tmp);
		free(tmp);
		index++;
	}
	return (EXIT_SUCCESS);
}
