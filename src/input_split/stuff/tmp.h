/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:51:58 by paulhenr          #+#    #+#             */
/*   Updated: 2024/03/25 16:18:04 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TMP_H
# define TMP_H

# include "linked_lists.h"
# include "typedefs.h"
# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

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

#define CR_MODE O_CREAT | O_TRUNC | O_WRONLY
#define AP_MODE O_CREAT | O_APPEND | O_RDWR

typedef struct s_proc
{
	int		infd;
	int		outfd;
	int		pp[2];
	char	**cmd;
	char	**envp;
}	t_proc;

typedef struct s_token
{
	char		*value;
	t_tk_name	type;
}				t_token;

int			classify_token(const char *str, t_list2	*list);
void		free_token(t_token *token, void (*del)(void *));
t_token		*new_token(char *value, int type, void (*del)(void *));

int			enclosed_in_quotes(const char *str);
t_list2		*input_split1(const char *str);
const char	*is_operator(const char *str);

// secondary/expand
char		*ft_strjoinlst(t_list2 *list);
int			expand_args(t_list2 *list, char **envp, t_token *token);
t_list2		*input_split2(t_token *token);
t_list2		*input_exp_split(const char *str);
char		*get_true_input(t_list2 *primary, char **envp);
char		*ft_strjoinlst_alt(t_list2 *list);

#endif