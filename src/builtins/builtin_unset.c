/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:59:12 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 14:44:32 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_proc *proc, t_main *main)
{
	char	opt[11];
	t_list2	*tmp;

	if (!proc->argv)
		return (get_exit_str(EXIT_FAILURE, main->exit_status), EXIT_FAILURE);
	if (!proc->argv->next)
		return (EXIT_SUCCESS);
	get_exit_str(EXIT_FAILURE, main->exit_status);
	if (has_invalid_opt(proc->argv))
	{
		ft_strlcpy(opt, "unset: ", 9);
		ft_strlcat(opt, proc->argv->next->data, 11 + 3);
		return (ft_perror(opt, "invalid option"), 1);
	}
	tmp = proc->argv->next;
	while (tmp)
	{
		main->envp = update_envp(main->envp, (char *)tmp->data, NULL);
		tmp = tmp->next;
	}
	if (!main->envp)
		return (EXIT_FAILURE);
	get_exit_str(EXIT_SUCCESS, main->exit_status);
	return (EXIT_SUCCESS);
}
