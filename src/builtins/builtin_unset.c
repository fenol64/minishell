/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:59:12 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/08 16:05:38 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_proc *proc, t_main *main)
{
	if (!proc->argv)
		return (0);
	get_exit_str(EXIT_FAILURE, main->exit_status);
	if (has_invalid_opt(proc->argv))
		return (ft_perror("unset", "invalid option"), 1);
	main->envp = update_envp(main->envp, (char *)proc->argv->next->data, NULL);
	if (!main->envp)
		return (1);
	get_exit_str(EXIT_SUCCESS, main->exit_status);
	return (0);
}