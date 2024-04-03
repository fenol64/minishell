/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:10:22 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/03 14:25:38 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../proc_creator/proc_creator.h"

//	builtins1.c
void	ts_putstr(const char *str);
int		ft_echo(t_proc *proc, t_main *main);
int		ft_cd(t_proc *proc, t_main *main);

//	builtins_envp.c
t_list2	*lst_from_envp(char **envp);
char	**envp_from_lst(t_list2 *envlist);
char	**update_envp(char **envp, char *name, char *new_value);

//	builtins_envp_utils.c
char	**cpy_envp(char **envp);

#endif