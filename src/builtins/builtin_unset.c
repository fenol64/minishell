/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:59:12 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/09 10:58:00 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_proc *proc, t_main *main)
{
	if (!proc->argv)
		return (EXIT_SUCCESS);
	get_exit_str(EXIT_FAILURE, main->exit_status);
	if (has_invalid_opt(proc->argv))
		return (ft_perror("unset", "invalid option"), 1);
	if (!proc->argv->next)
	{
		get_exit_str(EXIT_SUCCESS, main->exit_status);
		return (EXIT_SUCCESS);
	}
	main->envp = update_envp(main->envp, (char *)proc->argv->next->data, NULL);
	if (!main->envp)
		return (EXIT_FAILURE);
	get_exit_str(EXIT_SUCCESS, main->exit_status);
	return (EXIT_SUCCESS);
}
