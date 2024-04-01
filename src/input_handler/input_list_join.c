/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:28:51 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/01 09:37:00 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

char	*ft_strjoin_token_lst(t_list2 *list)
{
	char	*joined;
	size_t	len;
	t_list2	*tmp;

	len = 0;
	tmp = list;
	if (!list)
		return (ft_perror(__func__, ARGNULL), NULL);
	while (tmp)
	{
		len += ft_strlen(((t_token *)tmp->data)->value);
		tmp = tmp->next;
	}
	joined = malloc((len + 1) * sizeof(char));
	*joined = '\0';
	if (!joined)
		return (perror(__func__), NULL);
	while (list)
	{
		ft_strcat(joined, ((t_token *)list->data)->value);
		list = list->next;
	}
	return (joined);
}

char	*ft_strjoinlst(t_list2 *list)
{
	char	*joined;
	size_t	len;
	t_list2	*tmp;

	len = 0;
	tmp = list;
	if (!list)
		return (ft_perror(__func__, ARGNULL), NULL);
	while (tmp)
	{
		len += ft_strlen((char *)tmp->data);
		tmp = tmp->next;
	}
	joined = malloc((len + 1) * sizeof(char));
	*joined = '\0';
	if (!joined)
		return (perror(__func__), NULL);
	while (list)
	{
		ft_strcat(joined, (char *)list->data);
		list = list->next;
	}
	return (joined);
}

char	**matrix_from_list(t_list2	*list)
{
	size_t	index;
	size_t	size;
	char	**matrix;

	if (!list)
		return (ft_perror(__func__, ARGNULL), NULL);
	size = lst_size2(list);
	matrix = malloc(sizeof(char *) * (size + 1));
	if (!matrix)
		return (perror(__func__), NULL);
	index = 0;
	while (list)
	{
		matrix[index] = ft_strdup((char *)list->data);
		if (!matrix[index])
			return (perror(__func__), ft_free_matrix(matrix), NULL);
		index++;
		list = list->next;
	}
	matrix[index] = NULL;
	return (matrix);
}