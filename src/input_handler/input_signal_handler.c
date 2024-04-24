/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_signal_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:50:36 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/24 14:48:39 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"
#include <sys/ioctl.h>

int	g_signal = 0;

void	restore_fds(t_main *main)
{
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

static void	press_enter(void)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

static void	sig_handler(int signum)
{
	g_signal = signum;
	if (signum == SIGQUIT)
		return ;
	if (signum == SIGINT)
		press_enter();
}

void	setup_signals(void)
{
	struct termios		term;
	struct sigaction	sa1;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit(EXIT_FAILURE);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
	sa1.sa_handler = sig_handler;
	sigemptyset(&sa1.sa_mask);
	sigaddset(&sa1.sa_mask, SIGINT);
	sa1.sa_flags = 0;
	if (sigaction(SIGINT, &sa1, NULL) == -1)
	{
		perror(__func__);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa1, NULL) == -1)
	{
		perror(__func__);
		exit(EXIT_FAILURE);
	}
}
