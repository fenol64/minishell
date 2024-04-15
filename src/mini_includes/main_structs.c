/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:17:43 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 10:21:52 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_typedefs.h"

t_main	*new_main(char **envp)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
		return (perror(__func__), NULL);
	main->def_stdout = dup(STDOUT_FILENO);
	main->def_stdin = dup(STDIN_FILENO);
	if (main->def_stdin == -1 || main->def_stdout == -1)
		return (free_main(main), NULL);
	main->envp = envp;
	ft_memset(main->exit_status, '\0', EXSTR * sizeof(char));
	main->exit_status[0] = '0';
	main->init_status = false;
	return (main);
}

t_token	*new_token(char *value, int type, void (*del)(void *))
{
	t_token	*token;

	token = malloc(sizeof * token);
	if (!token)
	{
		if (del)
			del(value);
		return (perror(__func__), NULL);
	}
	token->value = value;
	token->type = type;
	return (token);
}

t_file	*new_file(void)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (perror(__func__), NULL);
	file->fd = -1;
	file->mode = 0;
	file->name = NULL;
	return (file);
}

t_proc	*new_proc(void)
{
	t_proc	*proc;

	proc = malloc(sizeof(t_proc));
	if (!proc)
		return (perror(__func__), NULL);
	proc->argv = NULL;
	proc->envp = NULL;
	proc->infiles = NULL;
	proc->outfiles = NULL;
	proc->pfd[0] = -1;
	proc->pfd[1] = -1;
	return (proc);
}
