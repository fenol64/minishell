/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:01:14 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/26 13:56:38 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#define FT_PERROR_BUFFER_SIZE 5124

int	ft_perror(const char *s1, const char *s2)
{
	static char	buffer[FT_PERROR_BUFFER_SIZE];

	buffer[0] = '\0';
	if (!s1 || !s2)
		return (ft_perror(__func__, "argument is NULL"), 1);
	if (!*s1 && !*s2)
		return (ft_perror(__func__, "all arguments are empty"), 1);
	if (ft_strlen(s1) + ft_strlen(s2) >= FT_PERROR_BUFFER_SIZE)
		return (ft_perror(__func__, "error msg is too big"), 1);
	if (*s1)
		ft_strcat(buffer, s1);
	if (*s1 && *s2)
		ft_strcat(buffer, ": ");
	if (*s2)
		ft_strcat(buffer, s2);
	ft_strcat(buffer, "\n");
	ft_putstr_fd(buffer, STDERR_FILENO);
	return (0);
}
