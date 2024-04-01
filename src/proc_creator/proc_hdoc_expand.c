/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_hdoc_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:54:10 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/01 13:14:35 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static char	*ft_getenv(char *name, char **envp)
{
	size_t	var_size;
	size_t	index;

	if (!envp || !*envp || !name)
		return (ft_perror(__func__, ARGNULL), NULL);
	index = 0;
	while (envp[index])
	{
		if (!ft_strchr(envp[index], '='))
			return (ft_perror(__func__, "Env doesn't have equal sign"), NULL);
		var_size = ft_strchr(envp[index], '=') - envp[index];
		if (!ft_strncmp(envp[index], name, var_size / sizeof(char)))
			return (ft_strchr(envp[index], '=') + sizeof(char));
		index++;
	}
	return ("");
}

static char	*expand_str(char *str, char **envp)
{
	char	*tmp;
	char	*new;

	tmp = str;
	if (*str != '$')
	{
		new = ft_strdup(str);
		free(tmp);
		return (new);
	}
	else if (str[0] == '$' && str[1] == '\0')
	{
		new = ft_strdup(str);
		free(tmp);
		return (new);
	}
	new = ft_getenv(str + 1, envp);
	return (free(tmp), ft_strdup(new));
}

char *hdoc_expand(const char *str, char **envp)
{
	char	*data;
	t_list2	*tmp2;
	t_list2	*tmp;

	tmp = input_exp_split(str);
	if (!tmp)
		return (NULL);
	tmp2 = tmp;
	while (tmp2)
	{
		data = (char *)tmp2->data;
		tmp2->data = (void *)expand_str(data, envp);
		tmp2 = tmp2->next;
	}
	data = ft_strjoinlst(tmp);
	lst_destroy2(tmp, free);
	return (data);
}
