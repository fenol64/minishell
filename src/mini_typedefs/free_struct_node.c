/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:22:46 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 10:31:50 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_typedefs.h"

void	free_token_node(void *arg)
{
	t_token	*token;

	token = (t_token *)arg;
	free_token(token, free);
}

void	free_proc_list(t_proc **procs, void (*del)(void *arg))
{
	size_t	index;

	index = 0;
	if (!procs)
		return ;
	while (procs[index])
	{
		free_proc(procs[index], del);
		index++;
	}
	free(procs);
}

void	del_file_node(void *arg)
{
	free_file((t_file *)arg, free);
}
