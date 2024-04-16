/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_runtime.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:26:53 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/16 10:41:23 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROC_RUNTIME_H
# define PROC_RUNTIME_H

# include "../mini_includes/minishell.h"
# include "../proc_creator/proc_creator.h"
# include <sys/wait.h>

//	input_handler.a
char	**matrix_from_lst(t_list2 *list);

//	proc_creator.a
int		is_builtin(char *cmd);
int		valid_path(const char *path, int mode);
int		valid_folder(const char *path, int mode);
int		valid_filepath(const char *path, int mode);

//	execute.c
int		execute_child(t_proc *proc, t_main *main);

#endif
