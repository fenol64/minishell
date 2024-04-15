/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:54:13 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 12:59:52 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLER_H
# define INPUT_HANDLER_H

# include "../mini_includes/mini_typedefs.h"
# include <stdbool.h>
# include <stdio.h>

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

//	input_list_validation.c
int			validate_input_list(t_list2 *input_list, t_main *main);
int			operator_type(t_token *token);

//	input_list_join.c
char		**matrix_from_lst(t_list2	*list);
char		*ft_strjoin_token_lst(t_list2 *list);
char		*ft_strjoinlst(t_list2 *list);
char		*ft_strjoinlstsep(t_list2 *list, const char *sep);

#endif