/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_signal_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:50:36 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/29 13:57:27 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"
#include <sys/ioctl.h>
#include <termios.h>

volatile int	g_signal = 0;

void	restore_fds(t_main *main)
{
	errno = 0;

	if (dup2(main->def_stdout, STDOUT_FILENO) == -1)
	{
		perror("Fatal error while restoring output");
		free_main(main);
		exit(EXIT_FAILURE);
	}
	if (dup2(main->def_stdin, STDIN_FILENO) == -1)
	{
		perror("Fatal error while restoring input");
		free_main(main);
		exit(EXIT_FAILURE);
	}
}

static void	discard_promp(void)
{
	int	fd;

	fd = open("/dev/null", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror(__func__);
		close(fd);
		exit(EXIT_FAILURE);
	}
	rl_replace_line("", 0);
	close(fd);
}

static void	sig_handler(int signum)
{
	g_signal = signum;
	if (signum == SIGCHLD)
	{
		while (waitpid(-1, NULL, WNOHANG) > 0)
			continue ;
		return ;
	}
	if (signum == SIGINT)
		discard_promp();
}

void	setup_signals(void)
{
	int					status;
	struct sigaction	sa1;
	struct sigaction	sa2;

	status = 0;
	sa1.sa_flags = SA_RESTART;
	sa2.sa_flags = SA_RESTART;
	sigemptyset(&sa1.sa_mask);
	sigemptyset(&sa2.sa_mask);
	sigaddset(&sa1.sa_mask, SIGINT);
	sigaddset(&sa1.sa_mask, SIGCHLD);
	sa1.sa_handler = sig_handler;
	sa2.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa2, NULL) == -1 && !status)
		status = -1;
	if (sigaction(SIGINT, &sa1, NULL) == -1 && !status)
		status = -1;
	if (sigaction(SIGCHLD, &sa1, NULL) == -1 && !status)
		status = -1;
	if (status == -1)
	{
		perror(__func__);
		exit(EXIT_FAILURE);
	}
}
