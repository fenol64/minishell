/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_runtime.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:26:53 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/25 14:58:04 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROC_RUNTIME_H
# define PROC_RUNTIME_H

# include "../mini_includes/minishell.h"
# include <sys/wait.h>

//	run_proc_utils.c
void	close_pipe(int pipe[2]);
void	write_hdoc(t_file *file, int fd);
t_file	*get_inputfile(t_proc *proc);
t_file	*get_outputfile(t_proc *proc);
void	exit_shell(t_main *main);

//	input_handler.a
char	**matrix_from_lst(t_list2 *list);

//	proc_creator.a
int		is_builtin(char *cmd);
int		valid_path(const char *path, int mode);
int		valid_folder(const char *path, int mode);
int		valid_filepath(const char *path, int mode);

//	execute.c
int		execute_cmd(t_proc *proc, t_main *main);
size_t	proc_len(t_main *main);

//	make_proc.c
int		ft_pipeline(t_main *main);
int		run_proc_primary(t_proc *proc, t_main *main);
int		run_proc_secondary(t_proc *proc, t_main *main);

#endif
