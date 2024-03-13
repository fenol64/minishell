/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:34:49 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/13 11:06:51 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strpdup(const char *start, const char *end)
{
	char		*new;
	size_t		index;
	const char	*new_end;

	if (!start)
		return (ft_perror(__func__, ARGNULL), NULL);
	if (end < start && end != NULL)
		return (ft_perror(__func__, ARGINV), NULL);
	index = 0;
	if (end > start)
		new = malloc(((end - start) * sizeof(char)) + sizeof(char));
	else
		new = malloc(((ft_strlen(start)) * sizeof(char)) + sizeof(char));
	if (!new)
		return (ft_perror(__func__, MEMFAIL), NULL);
	new_end = end;
	if (!end)
		new_end = ft_strchr(start, '\0');
	while (&start[index] != new_end)
	{
		new[index] = start[index];
		index++;
	}
	new[index] = '\0';
	return (new);
}
