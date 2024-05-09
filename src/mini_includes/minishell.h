/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:08:49 by fnascime          #+#    #+#             */
/*   Updated: 2024/04/26 13:51:48 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mini_typedefs.h"

# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>

//	builtins:		shell's builtins cd, pwd, env, echo, exit, unset, export
//	input_handler:	shell prompt parsing and expanding
//	proc_creator:	process struct initialization from parsed prompt
//		input/output/heredocs opening/closing, PATH search

/*------------------------------ Input Handler ------------------------------*/
//	input_split_primary.c
t_list2	*get_true_input(const char *input, t_main *main);
/*---------------------------------------------------------------------------*/

/*------------------------------- Proc Creator ------------------------------*/
//	proc_from_list.c
t_proc	**get_procs(t_main *main);
/*---------------------------------------------------------------------------*/

/*--------------------------------- Builtins --------------------------------*/
//	builtins1.c
int		ft_cd(t_proc *proc, t_main *main);
int		ft_pwd(t_proc *proc, t_main *main);
int		ft_env(t_proc *proc, t_main *main);
int		ft_echo(t_proc *proc, t_main *main);
int		ft_exit(t_proc *proc, t_main *main);

//	builtin_export/unset.c
int		ft_unset(t_proc *proc, t_main *main);
int		ft_export(t_proc *proc, t_main *main);
/*---------------------------------------------------------------------------*/

/*--------------------------------- PIPELINE---------------------------------*/
int		ft_pipeline(t_main *main);
/*---------------------------------------------------------------------------*/

/*------------------------------- Misc --------------------------------------*/
void	restore_fds(t_main *main);
void	setup_signals(void);
/*---------------------------------------------------------------------------*/

#endif
