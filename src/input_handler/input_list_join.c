/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:28:51 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 12:21:41 by paulhenr         ###   ########.fr       */
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
		if (!tmp->data)
			return (ft_perror(__func__, "list has null data"), NULL);
		len += ft_strlen(((t_token *)tmp->data)->value);
		tmp = tmp->next;
	}
	joined = malloc((len + 1) * sizeof(char));
	if (!joined)
		return (perror(__func__), NULL);
	*joined = '\0';
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
		if (!tmp->data)
			return (ft_perror(__func__, "list has null data"), NULL);
		len += ft_strlen((char *)tmp->data);
		tmp = tmp->next;
	}
	joined = malloc((len + 1) * sizeof(char));
	if (!joined)
		return (perror(__func__), NULL);
	*joined = '\0';
	while (list)
	{
		ft_strcat(joined, (char *)list->data);
		list = list->next;
	}
	return (joined);
}

char	**matrix_from_lst(t_list2	*list)
{
	size_t	index;
	size_t	size;
	char	**matrix;

	if (!list)
		return (ft_perror(__func__, ARGNULL), NULL);
	size = lst_len2(list);
	matrix = malloc(sizeof(char *) * (size + 1));
	if (!matrix)
		return (perror(__func__), NULL);
	index = 0;
	while (list)
	{
		if (!list->data)
			return (ft_perror(__func__, "list has null data")
				, ft_free_matrix(matrix), NULL);
		matrix[index] = ft_strdup((char *)list->data);
		if (!matrix[index])
			return (perror(__func__), ft_free_matrix(matrix), NULL);
		index++;
		list = list->next;
	}
	matrix[index] = NULL;
	return (matrix);
}

char	*ft_strjoinlstsep(t_list2 *list, const char *sep)
{
	char	*joined;
	size_t	len;
	t_list2	*tmp;

	len = 0;
	tmp = list;
	while (tmp)
	{
		len += ft_strlen((char *)tmp->data);
		if (tmp->next)
			len += ft_strlen(sep);
		tmp = tmp->next;
	}
	joined = ft_calloc((len + 1), sizeof(char));
	if (!joined)
		return (perror(__func__), NULL);
	while (list)
	{
		ft_strcat(joined, (char *)list->data);
		if (list->next)
			ft_strcat(joined, sep);
		list = list->next;
	}
	return (joined);
}
