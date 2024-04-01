/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:54:13 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/01 15:21:49 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLER_H
# define INPUT_HANDLER_H

# include <stdbool.h>
# include <stdio.h>
# include "stuff/libft.h"
# include "stuff/linked_lists.h"

# define EXSTR 4

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

typedef struct s_token
{
	char		*value;
	t_tk_name	type;
}				t_token;

typedef struct s_main
{
	int		std_out;
	int		std_in;
	char	exit_status[EXSTR];
	char	**envp;
}	t_main;

//	input_split_primary.c
t_list2		*input_split1(const char *str);
t_list2		*get_true_input(const char *input, t_main *main);

//	input_split_expand.c
int			expand_args(t_list2 *list, t_main *main, t_token *token);
char		*remove_quotes(char *str);
char		*ft_getenv(char *name, t_main *main);

//	input_split_secondary.c
t_list2		*input_split2(t_token *token);
t_list2		*input_exp_split(const char *str);

//	input_split_utils.c
int			enclosed_in_quotes(const char *str);
t_tk_name	classify_token(const char *str, t_list2	*list);
const char	*is_operator(const char *str);
void		get_exit_str(unsigned char nbr, char *fstring);

//	input_split_structs.c
void		free_token_node(void *arg);
void		free_main(t_main *main);
void		free_token(t_token *token, void (*del)(void *));
t_main		*new_main(char **envp);
t_token		*new_token(char *value, int type, void (*del)(void *));

//	input_list_validation.c
int			validate_input_list(t_list2 *input_list);
int			operator_type(t_token *token);

//	input_list_join.c
char		**matrix_from_lst(t_list2	*list);
char		*ft_strjoin_token_lst(t_list2 *list);
char		*ft_strjoinlst(t_list2 *list);


#endif