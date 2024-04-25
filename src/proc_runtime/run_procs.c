/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_procs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:12:37 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/25 14:47:22 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_includes/minishell.h"
#include "proc_runtime.h"

static int	get_stdin(t_proc *proc);
static int	get_stdout(t_proc *proc);

int	ft_pipeline(t_main *main)
{
	int		status;
	int		index;

	if (proc_len(main) < 2 && is_builtin(main->procs[0]->argv->data))
		return (execute_cmd(main->procs[0], main));
	index = 0;
	while (main->procs[index])
	{
		if (main->procs[index + 1])
			run_proc_primary(main->procs[index], main);
		else
			run_proc_secondary(main->procs[index], main);
		index++;
	}
	index--;
	waitpid(main->procs[index]->pid, &status, 0);
	if (WIFEXITED(status))
		get_exit_str(WEXITSTATUS(status), main->exit_status);
	while (--index > 0)
		waitpid(main->procs[index]->pid, &status, 0);
	restore_fds(main);
	return (EXIT_SUCCESS);
}
int	run_proc_primary(t_proc *proc, t_main *main)
{
	t_file	*file;

	if (pipe(proc->pfd) == -1)
		return (perror(__func__), exit(0), EXIT_FAILURE);
	get_stdin(proc);
	proc->pid = fork();
	if (proc->pid == -1)
		return (close_pipe(proc->pfd), EXIT_FAILURE);
	else if (proc->pid == 0)
	{
		close(proc->pfd[0]);
		file = get_outputfile(proc);
		if (file)
			get_stdout(proc);
		else
			dup2(proc->pfd[1], STDOUT_FILENO);
		close(proc->pfd[1]);
		execute_cmd(proc, main);
	}
	close(proc->pfd[1]);
	dup2(proc->pfd[0], STDIN_FILENO);
	close(proc->pfd[0]);
	return (EXIT_SUCCESS);
}

int	run_proc_secondary(t_proc *proc, t_main *main)
{
	if (pipe(proc->pfd) == -1)
		return (perror(__func__), exit(EXIT_FAILURE), 1);
	get_stdin(proc);
	proc->pid = fork();
	if (proc->pid == -1)
		return (close_pipe(proc->pfd), EXIT_FAILURE);
	else if (proc->pid == 0)
	{
		close(proc->pfd[0]);
		close(proc->pfd[1]);
		get_stdout(proc);
		execute_cmd(proc, main);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(proc->pfd[1]);
	close(proc->pfd[0]);
	return (EXIT_SUCCESS);
}

static int	get_stdin(t_proc *proc)
{
	t_file	*file;

	file = get_inputfile(proc);
	if (file && file->mode != -42)
	{
		if (dup2(file->fd, STDIN_FILENO) == -1)
			return (perror(__func__), exit(EXIT_FAILURE), 1);
		close(file->fd);
		file->fd = -1;
	}
	else if (file && file->mode == -42)
	{
		if (write(proc->pfd[1], file->name, ft_strlen(file->name)) == -1)
			return (perror(__func__), exit(EXIT_FAILURE), 1);
		if (dup2(proc->pfd[0], STDIN_FILENO) == -1)
			return (perror(__func__), exit(EXIT_FAILURE), 1);
	}
	return (0);
}

static int	get_stdout(t_proc *proc)
{
	t_file	*file;

	file = get_outputfile(proc);
	if (file)
	{
		if (dup2(file->fd, STDOUT_FILENO) == -1)
			return (perror(__func__), exit(EXIT_FAILURE), 1);
		close(file->fd);
		file->fd = -1;
	}
	else
	{
		if (dup2(proc->main->def_stdout, STDOUT_FILENO) == -1)
			return (perror(__func__), exit(EXIT_FAILURE), 1);
	}
	return (0);
}