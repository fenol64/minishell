/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:17:43 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/25 10:14:52 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_typedefs.h"

t_main	*new_main(char **envp)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
		return (perror(__func__), NULL);
	main->procs = NULL;
	main->input_list = NULL;
	main->envp = cpy_envp(envp);
	main->def_stdout = dup(STDOUT_FILENO);
	main->def_stdin = dup(STDIN_FILENO);
	if (!main->envp || (main->def_stdin == -1 || main->def_stdout == -1))
	{
		if (main->def_stdin != -1)
			close(main->def_stdin);
		if (main->def_stdout != -1)
			close(main->def_stdout);
		free_main(main);
		exit(EXIT_FAILURE);
	}
	ft_memset(main->exit_status, '\0', EXSTR * sizeof(char));
	main->inp_line = NULL;
	main->exit_status[0] = '0';
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

t_proc	*new_proc(t_main *main)
{
	t_proc	*proc;

	proc = malloc(sizeof(t_proc));
	if (!proc)
		return (perror(__func__), NULL);
	proc->main = main;
	proc->pid = -1;
	proc->argv = NULL;
	proc->envp = NULL;
	proc->infiles = NULL;
	proc->outfiles = NULL;
	proc->pfd[0] = -1;
	proc->pfd[1] = -1;
	return (proc);
}
