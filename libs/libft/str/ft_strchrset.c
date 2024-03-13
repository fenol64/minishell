/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:39:30 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/13 11:06:35 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchrset(const char *str, const char *charset)
{
	size_t	index;

	if (!str || !charset)
		return (ft_perror(__func__, ARGNULL), NULL);
	index = 0;
	while (str[index])
	{
		if (ft_incharset(str[index], charset))
			return ((char *)&str[index]);
		index++;
	}
	if (ft_incharset(str[index], charset))
		return ((char *)&str[index]);
	return (NULL);
}
