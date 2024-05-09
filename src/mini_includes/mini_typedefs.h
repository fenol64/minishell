/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_typedefs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:07:27 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/29 09:40:19 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TYPEDEFS_H
# define MINI_TYPEDEFS_H

//	deps
# include "libft.h"
# include "linked_lists.h"

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdint.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

# define EXSTR 4

extern volatile int		g_signal;
typedef struct s_main	t_main;
typedef struct s_proc	t_proc;

//	header with typedefs that are used across the program

//	token types
typedef enum s_tk_name
{
	ARG = 1,
	PIPE = 2,
	HERE_DOC = 3,
	HERE_DOC_ARG = 4,
	OUTPUT = 5,
	OUTPUT_ARG = 6,
	APPEND = 7,
	APPEND_ARG = 8,
	INPUT = 9,
	INPUT_ARG = 10
}	t_tk_name;

// token struct
typedef struct s_token
{
	char		*value;
	t_tk_name	type;
}				t_token;

//	file struct for storing input/output files and here_docs
typedef struct s_file
{
	int		fd;
	int		mode;
	char	*name;
}			t_file;

/*
	process struct, used for storing process information such as
	input files, output files and environment.
*/

struct s_proc
{
	int			pfd[2];
	char		**envp;
	pid_t		pid;
	t_main		*main;
	t_list2		*argv;
	t_list2		*outfiles;
	t_list2		*infiles;
};

/*
	main struct, contains the default FD's, a process list for cleanup
	shell's exit status and main environment
*/
struct s_main
{
	int		def_stdin;
	int		def_stdout;
	char	exit_status[EXSTR];
	char	*inp_line;
	char	**envp;
	t_proc	**procs;
	t_list2	*input_list;
};

//	main_structs.c
t_file	*new_file(void);
t_proc	*new_proc(t_main *main);
t_main	*new_main(char **envp);
t_token	*new_token(char *value, int type, void (*del)(void *));

//	free_structs.c
int		close_proc_files(t_proc *proc);
void	free_main(t_main *main);
void	free_file(t_file *file, void (*del)(void *arg));
void	free_token(t_token *token, void (*del)(void *arg));
void	free_proc(t_proc *proc, void (*del_arg)(void *arg));

//	free_struc_node.c
void	del_file_node(void *arg);
void	free_token_node(void *arg);

//	structs_utils.c
char	**cpy_envp(char **envp);
void	free_proc_list(t_proc **procs, void (*del)(void *arg));
void	get_exit_str(uint8_t nbr, char *fstring);

#endif