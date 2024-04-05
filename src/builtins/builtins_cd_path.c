/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:00:39 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/05 12:20:06 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*resolve_path(const char *anchor, char **arg);
static char	*get_absolue_path(const char *path);
static char	*get_relative_path(const char *path);

char	*get_targetdir(const char *path)
{
	char	*dir;

	if (!path)
		return (NULL);
	if (*path == '/')
		dir = get_absolue_path(path);
	else
		dir = get_relative_path(path);
	return (dir);
}

static char	*get_relative_path(const char *path)
{
	char	buffer[PATH_MAX];
	char	*tmp;
	char	**dirs;
	char	*tpath;

	dirs = ft_split(path, '/');
	if (!dirs) 
		return (perror(__func__), NULL);
	getcwd(buffer, PATH_MAX);
	tpath = resolve_path(buffer, dirs);
	if (!tpath)
		return (ft_free_matrix(dirs), NULL);
	tmp = tpath;
	if (!*tpath)
	{
		tpath = ft_strdup("/");
		free(tmp);
	}
	return (ft_free_matrix(dirs), tpath);
}

static char	*get_absolue_path(const char *path)
{
	char	*tmp;
	char	**dirs;
	char	*tpath;

	dirs = ft_split(path, '/');
	if (!dirs) 
		return (perror(__func__), NULL);
	tpath = resolve_path("/", dirs);
	if (!tpath)
		return (ft_free_matrix(dirs), NULL);
	tmp = tpath;
	if (!*tpath)
	{
		tpath = ft_strdup("/");
		free(tmp);
	}
	return (ft_free_matrix(dirs), tpath);
}

static char	*resolve_path(const char *anchor, char **arg)
{
	char	*str;
	char	**dirs;
	t_list2	*path;
	t_list2	*tmp;

	if (*anchor == '/' && ft_strlen(anchor) > 1)
		dirs = ft_split(anchor, '/');
	else
	{
		dirs = ft_calloc(sizeof(char *), 2);
		if (!dirs)
			return (perror(__func__), NULL);
		*dirs = ft_strdup("");
		if (!*dirs)
			return (perror(__func__), free(dirs), NULL);
	}
	path = lst_from_envp(dirs);
	tmp = lst_from_envp(arg);
	if (!dirs || !path || !tmp)
		return (ft_free_matrix(dirs), lst_destroy2(path, free),
				 lst_destroy2(tmp, free), NULL);
	lst_append2(&path, tmp);
	tmp = path;
	while (tmp)
	{
		str = (char *)tmp->data;
		if (!ft_strcmp(str, "..") || !ft_strcmp(str, "."))
		{
			if (ft_strcmp(str, "..") == 0)
				lst_del_node2(&path, tmp->prev, free);
			lst_del_node2(&path, tmp, free);
			tmp = path;
		}
		tmp = tmp->next;
	}
	str = ft_strjoinlstsep(path, "/");
	return (ft_free_matrix(dirs), lst_destroy2(path, free), str);
}
