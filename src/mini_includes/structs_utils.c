/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:56:30 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 12:59:26 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_typedefs.h"

char	**cpy_envp(char **envp)
{
	char	**cpy;
	size_t	size;

	if (!envp)
		return (ft_perror(__func__, ARGNULL), NULL);
	size = 0;
	while (envp[size])
		size++;
	cpy = malloc(sizeof(char *) * (size + 1));
	if (!cpy)
		return (perror(__func__), NULL);
	size = 0;
	while (envp[size])
	{
		cpy[size] = ft_strdup(envp[size]);
		size++;
	}
	cpy[size] = NULL;
	return (cpy);
}

int	close_proc_files(t_proc *proc)
{
	t_file	*file;
	t_list2	*tmp;
	t_list2	*tmp2;

	tmp = proc->infiles;
	while (tmp)
	{
		file = (t_file *)tmp->data;
		if (file->mode != -42 && file->fd != -1)
			close(file->fd);
		tmp = tmp->next;
	}
	tmp2 = proc->outfiles;
	while (tmp2)
	{
		file = (t_file *)tmp2->data;
		if (file->mode != -42 && file->fd != -1)
			close(file->fd);
		tmp2 = tmp2->next;
	}
	lst_destroy2(proc->infiles, del_file_node);
	lst_destroy2(proc->outfiles, del_file_node);
	proc->infiles = NULL;
	proc->outfiles = NULL;
	return (true);
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
	if (index > 0)
		--index;
	while (1)
	{
		rem = nbr % 10;
		fstring[index] = rem + '0';
		if (nbr == 0 || index == 0)
			break ;
		nbr /= 10;
		index--;
	}
}