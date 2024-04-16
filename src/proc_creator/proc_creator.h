/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_creator.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:01:17 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/16 12:19:19 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROC_CREATOR_H
# define PROC_CREATOR_H

# include "../mini_includes/mini_typedefs.h"
# include "../input_handler/input_handler.h"

//	proc_from_list.c
t_proc	**init_procs(t_list2 *list, t_main *main);
t_proc	**get_procs(t_list2 *list, t_main *main);

//	proc_creator_utils.c
void	del_file_node(void *arg);
char	*get_here_doc(t_file *file, t_main *main);

//	proc_hdoc_expand.c
char	*hdoc_expand(const char *str, t_main *main);

//	proc_open_files.c
int		close_proc_files(t_proc *proc);
int		open_proc_outfiles(t_proc *proc);
int		open_proc_infiles(t_proc *proc);

// proc_filepaths.c
int		is_builtin(char *cmd);
int		valid_path(const char *path, int mode);
int		valid_folder(const char *path, int mode);
int		valid_filepath(const char *path, int mode);

// proc_get_path.c
char	*get_path(t_proc *proc, t_main *main);

#endif