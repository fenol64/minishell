/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:59:04 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/26 12:45:13 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static char *get_str(t_list2 *node)
{
	if (node && node->data)
		return ((char *)node->data);
	return (NULL);
}

char	*get_path(t_proc *proc, t_main *main)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	*cmd;

	if (proc->argv && is_builtin(proc->argv->data))
		return ((char *)proc->argv->data);
	cmd = get_str(proc->argv);
	paths = ft_split(ft_getenv("PATH", main), ':');
	if (!paths)
		return (perror(__func__), NULL);
	i = -1;
	while (cmd && paths[++i])
	{
		tmp = ft_strsepjoin(paths[i], "/", cmd);
		if (!tmp)
			return (ft_free_matrix(paths), NULL);
		if (valid_filepath(tmp, O_RDONLY) && access(tmp, X_OK) == 0)
		{
			proc->argv->data = tmp;
			return (ft_free_matrix(paths), free(cmd), tmp);
		}
		free(tmp);
	}
	return (ft_free_matrix(paths), cmd);
}
