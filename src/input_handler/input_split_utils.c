/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:39:53 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/01 15:45:43 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

static int	classify_arg(t_list2 *list);

int	enclosed_in_quotes(const char *str)
{
	const char	*quotes = "\"'";

	return (ft_incharset(*str, quotes) && ft_strchr(str + 1, *str));
}

t_tk_name	classify_token(const char *str, t_list2	*list)
{
	size_t		index;
	const char	*set[] = {">>", "<<", ">", "<", "|", NULL};

	if (!str)
		return (ft_perror(__func__, ARGNULL), -1);
	index = 0;
	while (set[index])
	{
		if (ft_strncmp(str, set[index], ft_strlen(set[index])) == 0)
		{
			if (!ft_strcmp(set[index], ">"))
				return (OUTPUT);
			else if (!ft_strcmp(set[index], "<"))
				return (INPUT);
			else if (!ft_strcmp(set[index], ">>"))
				return (APPEND);
			else if (!ft_strcmp(set[index], "<<"))
				return (HERE_DOC);
			else if (!ft_strcmp(set[index], "|"))
				return (PIPE);
		}
		index++;
	}
	return (classify_arg(list));
}

const char	*is_operator(const char *str)
{
	size_t		index;
	const char	*set[] = {">>", "<<", ">", "<", "|", NULL};

	if (!str)
		return (NULL);
	index = 0;
	while (set[index])
	{
		if (ft_strncmp(str, set[index], ft_strlen(set[index])) == 0)
			return (set[index]);
		index++;
	}
	return (NULL);
}

void	get_exit_str(unsigned char nbr, char *fstring)
{
	size_t	rem;
	size_t	index;

	ft_memset(fstring, 0, EXSTR);
	index = 0 + (nbr == 0);
	rem = nbr;
	while (rem)
	{
		index++;
		rem /= 10;
	}
	fstring[index] = '\0';
	while (1)
	{
		index--;
		rem = nbr % 10;
		fstring[index] = rem + '0';
		if (nbr == 0)
			break ;
		nbr /= 10;
	}
}

static int	classify_arg(t_list2 *list)
{
	t_token	*tmp;

	if (list && list->prev)
	{
		tmp = (t_token *)list->prev->data;
		if (!ft_strcmp(tmp->value, ">"))
			return (OUTPUT_ARG);
		else if (!ft_strcmp(tmp->value, "<"))
			return (INPUT_ARG);
		else if (!ft_strcmp(tmp->value, ">>"))
			return (APPEND_ARG);
		else if (!ft_strcmp(tmp->value, "<<"))
			return (HERE_DOC_ARG);
	}
	return (ARG);
}
