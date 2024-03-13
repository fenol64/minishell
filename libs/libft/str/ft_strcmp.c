/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:51:37 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/13 11:06:39 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t				i;
	unsigned const char	*s1;
	unsigned const char	*s2;

	if (!str1 || !str2)
		return (ft_perror(__func__, ARGNULL), 0);
	i = 0;
	s1 = (unsigned const char *)str1;
	s2 = (unsigned const char *)str2;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
