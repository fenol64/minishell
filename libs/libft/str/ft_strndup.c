/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:57:01 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/25 15:57:34 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;
	size_t	index;

	index = 0;
	if (!s)
		return (ft_perror(__func__, ARG_NULL), NULL);
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (ft_perror(__func__, MEM_FAIL), NULL);
	while (s[index] && (index < n))
	{
		new[index] = s[index];
		index++;
	}
	new[index] = '\0';
	return (new);
}
