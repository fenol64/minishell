/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:30:15 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/09 10:20:12 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	validate_assign(char **opts);
static char	**get_new_envp(char **envp, const char *entry);

int	validate_export(t_list2	*argv)
{
	char	**opts;
	t_list2	*tmp;

	if (has_invalid_opt(argv))
		return (false);
	if (!argv->next)
		return (true);
	if (!ft_strchr((char *)argv->next->data, '='))
		return (false);
	tmp = argv->next;
	while (tmp)
	{
		if (*(char *)tmp->data == '=')
			return (false);
		opts = ft_split((char *)tmp->data, '=');
		if (!opts)
			return (perror(__func__), false);
		else if (!*opts)
			return (ft_free_matrix(opts), false);
		if (!validate_assign(opts))
			return (ft_free_matrix(opts), false);
		ft_free_matrix(opts);
		tmp = tmp->next;
	}
	return (true);
}

int	ft_export(t_proc *proc, t_main *main)
{
	char	*entry;
	t_list2	*tmp;

	get_exit_str(EXIT_FAILURE, main->exit_status);
	if (!validate_export(proc->argv))
		return (EXIT_FAILURE);
	tmp = proc->argv->next;
	while (tmp)
	{
		entry = (char *)tmp->data;
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
	return (new_envp);
}

static int	validate_assign(char **opts)
{
	size_t	index;
	char	*name;

	name = *opts;
	if (ft_matrix_len(opts) < 2)
		return (false);
	if (ft_isdigit(*name))
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
