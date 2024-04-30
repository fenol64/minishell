/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split_secondary_helper.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:41:15 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/30 09:45:31 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler"

char	*cpy_env_name(const char *str)
{
	size_t	index;

	index = 0;
	if (str[0] && str[1])
		index++;
	else if (str[0] && !str[1])
		return (ft_strpdup(str, str + 1));
	while (str[index] && ft_isalpha(str[index]))
		index++;
	return (ft_strpdup(str, &str[index]));
}