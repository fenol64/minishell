/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_procs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:12:37 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/29 14:32:49 by paulhenr         ###   ########.fr       */
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
		return (setup_builtin(main->procs[0]));
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
	get_exit_str(130, main->exit_status);
	if (waitpid(main->procs[index]->pid, &status, 0) > 0 && WIFEXITED(status))
	{
		get_exit_str(WEXITSTATUS(status), main->exit_status);
		index--;
		while (--index >= 0)
			waitpid(-1, NULL, 0);
	}
	return (restore_fds(main), EXIT_SUCCESS);
}
int	run_proc_primary(t_proc *proc, t_main *main)
{
	int		status;
	t_file	*file;

	if (pipe(proc->pfd) == -1)
		exit_shell(main);
	get_stdin(proc);
	proc->pid = fork();
	if (proc->pid == -1)
		exit_shell(main);
	else if (proc->pid == 0)
	{
		file = get_outputfile(proc);
		if (file)
			get_stdout(proc);
		else
			dup2(proc->pfd[1], STDOUT_FILENO);
		close_pipe(proc->pfd);
		execute_cmd(proc, main);
		status = ft_atoi(main->exit_status);
		free_main(main);
		exit(status);
	}
	dup2(proc->pfd[0], STDIN_FILENO);
	close_pipe(proc->pfd);
	return (EXIT_SUCCESS);
}

int	run_proc_secondary(t_proc *proc, t_main *main)
{
	int	status;

	if (pipe(proc->pfd) == -1)
		exit_shell(main);
	get_stdin(proc);
	proc->pid = fork();
	if (proc->pid == -1)
		exit_shell(main);
	else if (proc->pid == 0)
	{
		close_pipe(proc->pfd);
		get_stdout(proc);
		execute_cmd(proc, main);
		status = ft_atoi(main->exit_status);
		free_main(main);
		exit(status);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close_pipe(proc->pfd);
	return (EXIT_SUCCESS);
}

static int	get_stdin(t_proc *proc)
{
	t_file	*file;

	file = get_inputfile(proc);
	if (file && file->mode != -42)
	{
		if (dup2(file->fd, STDIN_FILENO) == -1)
			exit_shell(proc->main);
		close(file->fd);
		file->fd = -1;
	}
	else if (file && file->mode == -42)
	{
		if (write(proc->pfd[1], file->name, ft_strlen(file->name)) == -1)
			exit_shell(proc->main);
		if (dup2(proc->pfd[0], STDIN_FILENO) == -1)
			exit_shell(proc->main);
		close(proc->pfd[1]);
		proc->pfd[1] = -1;
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