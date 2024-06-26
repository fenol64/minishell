/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:10:22 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/29 12:07:02 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../mini_includes/mini_typedefs.h"
# include "../proc_creator/proc_creator.h"
# include <linux/limits.h>

//	builtins1.c
int		ft_cd(t_proc *proc, t_main *main);
int		ft_pwd(t_proc *proc, t_main *main);
int		ft_env(t_proc *proc, t_main *main);
int		ft_echo(t_proc *proc, t_main *main);
int		ft_exit(t_proc *proc, t_main *main);

//	builtins_envp.c
t_list2	*lst_from_envp(char **envp);
char	**envp_from_lst(t_list2 *envlist);
char	**update_envp(char **envp, char *name, char *new_value);

//	builtins_utils.c
int		ts_putstr(const char *str);
int		has_invalid_opt(t_list2 *argv);
bool	ft_strnumeric(const char *str);
char	**cpy_envp(char **envp);

// builtin_export.c
int		validate_export(t_list2	*argv);
int		ft_export(t_proc *proc, t_main *main);

// builtin_unset.c
int		ft_unset(t_proc *proc, t_main *main);

#endif