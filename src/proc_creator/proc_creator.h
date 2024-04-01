/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_creator.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:01:17 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/28 15:06:31 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROC_CREATOR_H
# define PROC_CREATOR_H

# include "../input_handler/input_handler.h"
# include "../input_handler/stuff/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_file
{
	int		fd;
	int		mode;
	char	*name;
}			t_file;

typedef struct s_proc
{
	int			pfd[2];
	char		**envp;
	t_list2		*argv;
	t_list2		*outfiles;
	t_list2		*infiles;
}				t_proc;


// proc_creator_structs.c

t_proc	*new_proc(void);
void	free_proc(t_proc *proc, void (*del_arg)(void *a)
			, void (*del_file)(void *a));
t_file	*new_file(void);
void	free_file(t_file *file, void (*del)(void *arg));

void	free_proc_list(t_proc **procs, void (*del)(void *arg));

// proc_from_list.c

t_proc	**get_procs(t_list2 *input_list, char **envp);

// proc_creator_utils.c
void	del_file_node(void *arg);
char	*get_here_doc(t_file *file);

#endif