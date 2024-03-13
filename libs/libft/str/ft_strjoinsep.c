/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinsep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:17:40 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/13 11:23:01 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsepjoin(const char *s1, const char *sep, const char *s2)
{
	char	*joined;
	char	*last;

	size_t (*f)(const char *str);
	if (!s1 || !sep || !s2)
		return (ft_perror(__func__, ARGNULL), NULL);
	f = ft_strlen;
	joined = ft_calloc((f(s1) + f(s2) + f(sep) + 1), sizeof(char));
	if (!joined)
		return (ft_perror(__func__, MEMFAIL), NULL);
	last = ft_stpcpy(joined, s1);
	last = ft_stpcpy(last, sep);
	last = ft_stpcpy(last, s2);
	return (joined);
}
