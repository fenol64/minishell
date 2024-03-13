/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_incharset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:48:54 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/13 10:49:19 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_incharset(const char c, const char *charset)
{
	size_t	index;

	if (!charset)
		return (false);
	index = 0;
	while (charset[index])
	{
		if (c == charset[index])
			return (true);
		index++;
	}
	return (false);
}
