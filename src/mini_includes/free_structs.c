/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:20:31 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 15:54:42 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_typedefs.h"

void	free_main(t_main *main)
{
	if (!main)
		return ;
	if (main->def_stdout != -1)
		close(main->def_stdout);
	if (main->def_stdin != -1)
		close(main->def_stdin);
	ft_free_matrix(main->envp);
	free_proc_list(main->procs, free);
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
