/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_hdoc_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:54:10 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/03 10:08:25 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static char	*expand_str(char *str, t_main *main)
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
	new = ft_getenv(str + 1, main);
	return (free(tmp), ft_strdup(new));
}

char	*hdoc_expand(const char *str, t_main *main)
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
		tmp2->data = (void *)expand_str(data, main);
		tmp2 = tmp2->next;
	}
	data = ft_strjoinlst(tmp);
	lst_destroy2(tmp, free);
	return (data);
}
