/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:27:33 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/05 10:45:33 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		*swap(char *s1, char *s2)
{
	if (!s2)
		return (free(s1), NULL);
	free(s1);
	s1 = s2;
	return ((void *)s1);
}

static t_list2	*lst_getenv(t_list2 *envlist, char *name)
{
	char	*str;
	size_t	index;

	while (envlist)
	{
		str = (char *)envlist->data;
		index = ((ft_strchr(str, '=') - str) / sizeof(char));
		if (ft_strncmp(str, name, index) == 0)
			return (envlist);
		envlist = envlist->next;
	}
	return (NULL);
}

t_list2	*lst_from_envp(char **envp)
{
	size_t	index;
	t_list2	*tmp;
	t_list2	*node;

	tmp = NULL;
	index = 0;
	if (!envp)
		return (NULL);
	while (envp[index])
	{
		node = new_node2(ft_strdup(envp[index]), free);
		lst_append2(&tmp, node);
		if (!node || !node->data)
			return (perror(""), lst_destroy2(first_node(tmp), free), NULL);
		index++;
	}
	return (first_node(tmp));
}

char	**envp_from_lst(t_list2 *envlist)
{
	char	**envp;
	size_t	index;
	size_t	size;

	if (!envlist)
		return (NULL);
	size = lst_len2(envlist);
	envp = ft_calloc((size + 1), sizeof(char *));
	if (!envp)
		return (perror(__func__), NULL);
	index = 0;
	while (envlist)
	{
		if (!envlist->data)
		{
			lst_destroy2(first_node(envlist), free);
			return (ft_free_matrix(envp), NULL);
		}
		envp[index] = ft_strdup((char *)envlist->data);
		if (!envp[index])
			return (perror(__func__), ft_free_matrix(envp), NULL);
		index++;
		envlist = envlist->next;
	}
	return (envp);
}

char	**update_envp(char **envp, char *name, char *new_value)
{
	t_list2	*node;
	t_list2	*entry;
	t_list2	*envlist;

	if (!envp || !name || (!name && !new_value))
		return (NULL);
	envlist = lst_from_envp(envp);
	ft_free_matrix(envp);
	if (!envlist)
		return (NULL);
	entry = lst_getenv(envlist, name);
	if (!entry && name && new_value)
	{
		node = new_node2(ft_strsepjoin(name, "=", new_value), free);
		if (!node || !node->data)
			return (lst_destroy2(envlist, free), NULL);
		lst_append2(&envlist, node);
	}
	else if (entry && name && new_value == NULL)
		lst_del_node2(&envlist, entry, free);
	else if (entry && name && new_value)
		entry->data = swap(entry->data, ft_strsepjoin(name, "=", new_value));
	envp = envp_from_lst(envlist);
	return (lst_destroy2(envlist, free), envp);
}
