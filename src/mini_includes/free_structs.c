/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:20:31 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 10:30:54 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_typedefs.h"

void	free_main(t_main *main)
{
	if (!main)
		return ;
	if (main->std_out != -1)
		close(main->std_out);
	if (main->std_in != -1)
		close(main->std_in);
	ft_free_matrix(main->envp);
	free(main);
}

void	free_token(t_token *token, void (*del)(void *arg))
{
	if (del)
		del(token->value);
	free(token);
}

void	free_file(t_file *file, void (*del)(void *arg))
{
	if (!file)
		return ;
	if (del)
		del(file->name);
	free(file);
}

void	free_proc(t_proc *proc, void (*del_arg)(void *arg))
{
	if (!proc)
		return ;
	close_proc_files(proc);
	lst_destroy2(proc->argv, del_arg);
	free(proc);
}