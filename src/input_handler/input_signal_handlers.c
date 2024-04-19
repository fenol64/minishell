/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_signal_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:50:36 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/19 13:14:22 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

static int	press_enter(void)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("Fatal error while setting up pipe");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("Fatal error while redirecting output");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	write(STDOUT_FILENO, "\n", 1);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("Fatal error while redirecting input");
		close(fd[0]);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
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
	struct sigaction sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror(__func__);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror(__func__);
		exit(EXIT_FAILURE);
	}
}
