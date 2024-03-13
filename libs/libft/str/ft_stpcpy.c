/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:55:43 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/13 11:10:22 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*stpcpy(char *dst, const char *src)
{
	size_t	index;

	if (!dst || !src)
		return (ft_perror(__func__, ARGNULL), NULL);
	index = 0;
	while (src[index])
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (&dst[index]);
}
